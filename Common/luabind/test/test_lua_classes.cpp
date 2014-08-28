#include <boost/tokenizer.hpp>

#include "test.h"
#include <iostream>

namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct base
	{
		virtual ~base() 
		{
//			std::cout << "~base\n";
			feedback = -1;
		}

		virtual const char* f()
		{
			return "base";
		}
	};

	struct baseWrap : base
	{

		luabind::object self_;
		baseWrap(const luabind::object& self): self_(self) {}

		static const char* fS(base* obj)
		{
			return obj->base::f();
		}

		virtual const char* f()
		{
			return luabind::call_member<const char*>(self_, "f");
		}
	};

	struct simple_class
	{
		void f()
		{
			feedback = 3;
		}
	};

	struct no_copy
	{
		no_copy() {}
		virtual void f() = 0;	
	private:
		no_copy(const no_copy&) {}
	};

	void set_feedback(int n)
	{ feedback = n; }

} // anonymous namespace


bool test_lua_classes()
{
	using namespace luabind;

	{
	lua_State* L = lua_open();
	lua_baselibopen(L);
	lua_closer c(L);
	int top = lua_gettop(L);

	open(L);

	module(L)
	[
		class_<no_copy>("no copy"),
	
		class_<base, baseWrap>("base")
			.def(constructor<>())
			.def("f", &baseWrap::fS),

		class_<simple_class>("simple_class")
			.def(constructor<>())
			.def("f", &simple_class::f),

		def("set_feedback", &set_feedback)
	];

	dostring(L, "class 'derived' (base)\n"
			"function derived:__init() super() end\n"
			"function derived:f() return 'derived -> ' .. base.f(self) end\n");

	dostring(L, "function create_derived() return derived() end");

	base* ptr = call_function<base*>(L, "create_derived");

	if (std::string("derived -> base") != ptr->f()) return false;

	dostring(L, "class 'simple_derative' (simple_class)");
	dostring(L, "function simple_derative:__init() super() end\n");
	dostring(L, "a = simple_derative()");
	dostring(L, "a:f()");
	if (feedback != 3) return false;

	dostring(L, "class 'simple_lua_class'\n");
	dostring(L, "function simple_lua_class:__init()\n"
						"super()\n"
						"self.test_var = 1\n"
						"end\n"
						"function simple_lua_class:f()\n"
						"g = 5\n"
						"end\n");
	dostring(L, 	"a = simple_lua_class()");
	dostring(L,  "a:f()");
	if (feedback != 3) return false;
	object g = get_globals(L)["g"];
	if (object_cast<int>(g) != 5) return false;

	if (top != lua_gettop(L)) return false;

	dostring(L, "a = derived()");


	}

	if (feedback != -1) return false;


	{
		lua_State* L = lua_open();
		lua_baselibopen(L);
		lua_closer c(L);

		open(L);

		function(L, "set_feedback", &set_feedback);

		dostring(L, "class 'simple'");
		dostring(L, "function simple:__init() set_feedback(321) end");
		dostring(L, "function simple:__finalize() set_feedback(123) end");

		dostring(L, "a = simple()");

		if (feedback != 321) return false;
	}

	if (feedback != 123) return false;
	
	return true;
}

