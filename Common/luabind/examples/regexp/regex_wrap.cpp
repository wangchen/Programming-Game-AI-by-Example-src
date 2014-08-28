#include <boost/cregex.hpp> 

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include <luabind/luabind.hpp>


void wrap_regex(lua_State* L)
{
	using boost::RegEx;
	using namespace luabind;

	class_<RegEx>(L, "regex")
		.def(constructor<const char*>())
		.def(constructor<const char*, bool>())
		.def("match", (bool(RegEx::*)(const char*, unsigned int))&RegEx::Match)
		.def("search", (bool(RegEx::*)(const char*, unsigned int))&RegEx::Search)
		.def("what", &RegEx::What)
		.def("matched", &RegEx::Matched)
		.def("length", &RegEx::Length)
		.def("position", &RegEx::Position)
		.enum_("flags")
		[
			value("match_default", boost::match_default),
			value("match_prev_avail", boost::match_prev_avail),
			value("match_not_bob", boost::match_not_bob)
		]
		;
}

void test_wrap_regex()
{
	lua_State* L = lua_open();
	lua_baselibopen(L);
	lua_strlibopen(L);
	
	wrap_regex(L);
	
	lua_dofile(L, "regex.lua");
	
	lua_close(L);
}

