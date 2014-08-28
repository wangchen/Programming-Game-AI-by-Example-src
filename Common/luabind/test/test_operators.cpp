#include "test.h"
#include <iostream>

extern "C"
{
	#include "lualib.h"
}


namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct operator_tester
	{
		int operator+(int) const
		{
			feedback = 1;
			return 4;
		}

		float operator-() const
		{
			feedback = 2;
			return 4.6f;
		}

		float operator()() const
		{
			feedback = 3;
			return 3.5f;
		}

		float operator()(int a) const
		{
			feedback = 4;
			return 3.5f + a;;
		}

		float operator()(int a)
		{
			feedback = 7;
			return 3.5f + a;;
		}

	};

	int operator+(int, const operator_tester&)
	{
		feedback = 5;
		return 2;
	}

	struct operator_tester2
	{
	};

	float operator+(const operator_tester&, const operator_tester2&)
	{
		feedback = 6;
		return 6.3f;
	}

	struct operator_tester3: public operator_tester {};

	const operator_tester* make_const_test()
	{
		static operator_tester o;
		return &o;
	}

	std::ostream& operator<<(std::ostream& os, const operator_tester&)
	{
		os << "operator_tester"; feedback = 63; return os;
	}
	
} // anonymous namespace

bool test_operators()
{
	using namespace luabind;

	lua_State* L = lua_open();
	lua_closer c(L);
	lua_baselibopen(L);

	int top = lua_gettop(L);

	open(L);

	if (feedback != 0) return false;

	module(L)
	[
		class_<operator_tester>("operator_tester")
			.def(constructor<>())
			.def(tostring(const_self))
			.def(self + int())
			.def(other<int>() + self)
			.def(-self)
			.def(self())
			.def(const_self(int()))
			.def(self(int())),

		class_<operator_tester2>("operator_tester2")
			.def(constructor<>())
			.def(other<const operator_tester&>() + self),

		class_<operator_tester3, bases<operator_tester> >("operator_tester3")
			.def(constructor<>()),
	
		def("make_const_test", &make_const_test)
	];
	
	if (feedback != 0) return false;

	if (dostring(L, "test = operator_tester()")) return false;
	if (dostring(L, "test2 = operator_tester2()")) return false;
	if (dostring(L, "test3 = operator_tester3()")) return false;

	if (dostring(L, "test()")) return false;
	if (feedback != 3) return false;
	if (dostring(L, "test(5)")) return false;
	if (feedback != 7) return false;

	dostring(L, "const_test = make_const_test()");
	if (dostring(L, "const_test(5)")) return false;
	if (feedback != 4) return false;

	if (dostring(L, "a = -test")) return false;
	if (feedback != 2) return false;

	if (dostring(L, "a = test + test2")) return false;
	if (feedback != 6) return false;

	if (dostring(L, "a = 2 + test")) return false;
	if (feedback != 5) return false;

	if (dostring(L, "a = test + 2")) return false;
	if (feedback != 1) return false;

	if (dostring(L, "a = test3 + 6")) return false;
	if (feedback != 1) return false;

	if (dostring(L, "a = test3 + test2")) return false;
	if (feedback != 6) return false;

	if (dostring(L, "a = tostring(test)")) return false;
	if (feedback != 63) return false;

	const char* prog =
		"class 'my_class'\n"
		"function my_class:__add(lhs)\n"
		"	return my_class(self.val + lhs.val)\n"
		"end\n"
		"function my_class:__init(a)\n"
		"	self.val = a\n"
		"end\n"
		"function my_class:__sub(v)\n"
		"	if (type(self) == 'number') then\n"
		"		return my_class(self - v.val)\n"
		"	elseif (type(v) == 'number') then\n"
		"		return my_class(self.val - v)\n"
		"	else\n"
		"		return my_class(self.val - v.val)\n"
		"	end\n"
		"end\n"
		"a = my_class(3)\n"
		"b = my_class(7)\n"
		"c = a + b\n"
		"d = a - 2\n"
		"d = 10 - d\n"
		"d = d - b\n";

	if (dostring(L, prog)) return false;
	object var_c = get_globals(L)["c"];
	if (object_cast<int>(var_c["val"]) != 10) return false;

	object var_d = get_globals(L)["d"];
	if (object_cast<int>(var_d["val"]) != 2) return false;
	
	if (top != lua_gettop(L)) return false;

	return true;
}
