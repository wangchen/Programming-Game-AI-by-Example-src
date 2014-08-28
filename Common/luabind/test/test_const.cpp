#include "test.h"

namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct A
	{
		const A* f() { return this; }

		void g() const { feedback = 1; }
		void g() { feedback = 2; }
	};

} // anonymous namespace

bool test_const()
{
	using namespace luabind;

	lua_State* L = lua_open();
	lua_closer c(L);
	int top = lua_gettop(L);

	open(L);

	typedef void(A::*g1_t)();
	typedef void(A::*g2_t)() const;
	
	g1_t g1 = &A::g;
	g2_t g2 = &A::g;

	module(L)
	[
		class_<A>("A")
			.def(constructor<>())
			.def("f", &A::f)
			.def("g", /*(void(A::*)() const) &A::g*/ g1)
			.def("g", /*(void(A::*)()) &A::g*/ g2)
	];

	if (dostring(L, "a = A()")) return false;
	if (dostring(L, "a:g()")) return false;
	if (feedback != 2) return false;

	if (dostring(L, "a2 = a:f()")) return false;
	if (dostring(L, "a2:g()")) return false;
	if (feedback != 1) return false;

	if (top != lua_gettop(L)) return false;

	return true;
}
