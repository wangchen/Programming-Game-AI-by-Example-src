#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
}

//#define LUABIND_NO_ERROR_CHECKING
//#define LUABIND_DONT_COPY_STRINGS
//#define LUABIND_NO_EXCEPTIONS

#include <luabind/luabind.hpp>
#include <luabind/dependency_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/copy_policy.hpp>
#include <luabind/container_policy.hpp>
#include <luabind/discard_result_policy.hpp>

bool dostring(lua_State* L, const char* str);
int dostring2(lua_State* L, const char* str);

struct lua_closer
{
	lua_State* L;
	lua_closer(lua_State* L_): L(L_) {}
	void release() { if (L) {lua_close(L); L = 0; } }
	~lua_closer() { if (L != 0) lua_close(L); }
};


bool test_operators();
bool test_attributes();
bool test_construction();
bool test_implicit_cast();
bool test_const();
bool test_exceptions();
bool test_null_pointer();
bool test_policies();
bool test_lua_classes();
bool test_free_functions();
bool test_object();
bool test_held_type();
bool test_iterator();
bool test_scope();
bool test_yield();

#endif
