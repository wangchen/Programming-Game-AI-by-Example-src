#include "test.h"

namespace
{

	struct A
	{
		A* f() { return 0; }
	};

	A* get_pointer()
	{
		return 0;
	}

} // anonymous namespace


bool test_null_pointer()
{
	using namespace luabind;

	lua_State* L = lua_open();
	lua_closer c(L);
	int top = lua_gettop(L);

	open(L);

	module(L)
	[
		class_<A>("A")
			.def(constructor<>())
			.def("f", &A::f),

		def("get_pointer", get_pointer)
	];
	if (dostring(L, "e = get_pointer()")) return false;

	lua_pushstring(L, "e");
	lua_gettable(L, LUA_GLOBALSINDEX);
	if (!lua_isnil(L, -1)) return false;
	lua_pop(L, 1);

	if (dostring(L, "a = A() e = a:f()")) return false;
	lua_pushstring(L, "e");
	lua_gettable(L, LUA_GLOBALSINDEX);
	if (!lua_isnil(L, -1)) return false;
	lua_pop(L, 1);

	if (top != lua_gettop(L)) return false;

	return true;
}
