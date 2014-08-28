#include "test.h"

namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct A {};
	struct B: public A {};

	struct test_implicit
	{
		void f(A*) { feedback = 1; }
		void f(B*) { feedback = 2; }
	};

} // anonymous namespace

bool test_implicit_cast()
{
	using namespace luabind;

	lua_State* L = lua_open();
	lua_closer c(L);
	int top = lua_gettop(L);

	open(L);

	typedef void (test_implicit::*f1)(A*);
	typedef void (test_implicit::*f2)(B*);

	module(L)
	[
		class_<A>("A")
			.def(constructor<>()),
	
		class_<B, A>("B")
			.def(constructor<>()),
	
		class_<test_implicit>("test")
			.def(constructor<>())
			.def("f", (f1) &test_implicit::f)
			.def("f", (f2) &test_implicit::f)
	];

	if (dostring(L, "a = A()")) return false;
	if (dostring(L, "b = B()")) return false;
	if (dostring(L, "t = test()")) return false;

	if (dostring(L, "t:f(a)")) return false;
	if (feedback != 1) return false;

	if (dostring(L, "t:f(b)")) return false;
	if (feedback != 2) return false;

	if (top != lua_gettop(L)) return false;

	return true;
}
