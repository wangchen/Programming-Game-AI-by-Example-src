#include "test.h"
#include <iostream>

namespace
{
	using namespace luabind;
	LUABIND_ANONYMOUS_FIX int feedback1 = 0;
	LUABIND_ANONYMOUS_FIX int feedback2 = 0;
	LUABIND_ANONYMOUS_FIX int feedback3 = 0;
	LUABIND_ANONYMOUS_FIX int feedback4 = 0;
	LUABIND_ANONYMOUS_FIX int feedback5 = 0;

	void test_object_param(const object& table)
	{
		if (table.type() == LUA_TTABLE)
		{
			feedback1 = 1;

			feedback2 = object_cast<int>(table["oh"]);

			feedback3 = 0;
			for (object::array_iterator i = table.abegin(); i != table.aend(); ++i)
			{
				feedback3 += object_cast<int>(*i);
			}

			feedback4 = 0;
			for (object::iterator j = table.begin(); j != table.end(); ++j)
			{
				feedback4 += object_cast<int>(*j);
			}

			feedback5 = 0;
			for (object::raw_iterator j = table.raw_begin(); j != table.raw_end(); ++j)
			{
				feedback5 += object_cast<int>(*j);
			}

			table["blurp"] = 5;

		}
		else
		{
			feedback1 = 2;

			if (table.type() != LUA_TNIL)
			{
				feedback2 = 1;
			}
			else
			{
				feedback2 = 2;
			}
		}
	}

	int test_fun()
	{
		feedback1 = 3;
		return 42;
	}

	struct test_param
	{
		~test_param() { feedback1 = 30; }
	};

	void test_match(const luabind::object& o)
	{
		feedback1 = 28;
	}

	void test_match(int i)
	{
		feedback1 = 27;
	}

} // anonymous namespace

bool test_object()
{
	using namespace luabind;

	lua_State* L = lua_open();
	int top = lua_gettop(L);
	{
		open(L);

		module(L)
		[
			def("test_object_param", &test_object_param),
			def("test_fun", &test_fun),
			def("test_match", (void(*)(const luabind::object&))&test_match),
			def("test_match", (void(*)(int))&test_match),
		
			class_<test_param>("test_param")
				.def(constructor<>())
		];

		dostring(L, "t = 2");
		dostring(L, "test_object_param(t)");
		if (feedback1 != 2) return false;
		if (feedback2 != 1) return false;

		dostring(L, "test_object_param(nil)");
		if (feedback1 != 2) return false;
		if (feedback2 != 2) return false;

		dostring(L, "t = { ['oh'] = 4, 3, 5, 7, 13 }");
		dostring(L, "test_object_param(t)");
		if (feedback1 != 1) return false;
		if (feedback2 != 4) return false;
		if (feedback3 != 28) return false;
		if (feedback4 != 32) return false;
		if (feedback5 != 32) return false;

		object g = get_globals(L);

		object t = g["t"];
		if (t.type() != LUA_TTABLE) return false;

		object blurp = t["blurp"];
		if (object_cast<int>(blurp) != 5) return false;

		object fun = g["test_fun"];
		object ret = fun();
		if (object_cast<int>(ret) != 42) return false;
		if (feedback1 != 3) return false;

		dostring(L, "function test_param_policies(x, y) end");
		object test_param_policies = g["test_param_policies"];
		int a = test_param_policies.type();
		if (a != LUA_TFUNCTION) return false;
		// call the function and tell lua to adopt the pointer passed as first argument
		test_param_policies(5, new test_param())[adopt(_2)];

		dostring(L, "test_match(7)");
		if (feedback1 != 27) return false;
		dostring(L, "test_match('oo')");
		if (feedback1 != 28) return false;

		dostring(L, "function test_object_policies(a) glob = a\nreturn 6\nend");
		object test_object_policies = g["test_object_policies"];
		object ret_val = test_object_policies("teststring")[detail::null_type()];
		if (object_cast<int>(ret_val) != 6) return false;
		if (object_cast<std::string>(g["glob"]) != "teststring") return false;
		if (object_cast<std::string>(g.at("glob")) != "teststring") return false;
		if (object_cast<std::string>(g.raw_at("glob")) != "teststring") return false;
	}

	if (top != lua_gettop(L)) return false;

	lua_close(L);

	// make sure lua adopted the pointer by checking that it has been deleted
	if (feedback1 != 30) return false;

	return true;
}
