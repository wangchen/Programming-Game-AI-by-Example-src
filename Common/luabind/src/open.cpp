// Copyright (c) 2003 Daniel Wallin and Arvid Norberg

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

extern "C"
{
	#include "lua.h"
}

#include <luabind/luabind.hpp>

using namespace luabind::detail;

void luabind::detail::add_operator_to_metatable(lua_State* L, int op_index)
{
	lua_pushstring(L, get_operator_name(op_index));
	lua_pushnumber(L, op_index);
	lua_pushcclosure(L, &class_rep::operator_dispatcher, 1);
	lua_settable(L, -3);
}

int luabind::detail::create_cpp_class_metatable(lua_State* L)
{
	lua_newtable(L);

	// mark the table with our (hopefully) unique tag
	// that says that the user data that has this
	// metatable is a class_rep
	lua_pushstring(L, "__luabind_classrep");
	lua_pushboolean(L, 1);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	lua_pushcclosure(L, &garbage_collector_s<detail::class_rep>::apply, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__call");
	lua_pushcclosure(L, &class_rep::constructor_dispatcher, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, &class_rep::static_class_gettable, 0);
	lua_rawset(L, -3);

	return detail::ref(L);
}

int luabind::detail::create_cpp_instance_metatable(lua_State* L)
{
	lua_newtable(L);

	// just indicate that this really is a class and not just any user data
	lua_pushstring(L, "__luabind_class");
	lua_pushboolean(L, 1);
	lua_rawset(L, -3);

	// __index and __newindex will simply be references to the class_rep
	// wich in turn has it's own metamethods for __index and __newindex
	lua_pushstring(L, "__index");
	lua_pushcclosure(L, &class_rep::gettable_dispatcher, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, &class_rep::settable_dispatcher, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	//lua_pushcclosure(L, &garbage_collector_s<detail::object_rep>::apply, 0);
	lua_pushcclosure(L, detail::object_rep::garbage_collector, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gettable");
	lua_pushcclosure(L, &class_rep::static_class_gettable, 0);
	lua_rawset(L, -3);

	for (int i = 0; i < number_of_operators; ++i) add_operator_to_metatable(L, i);

	// store a reference to the instance-metatable in our class_rep
	assert((lua_type(L, -1) == LUA_TTABLE) && "internal error, please report");

	return detail::ref(L);
}

int luabind::detail::create_lua_class_metatable(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "__luabind_classrep");
	lua_pushboolean(L, 1);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	lua_pushcclosure(L, &detail::garbage_collector_s<detail::class_rep>::apply, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, &class_rep::lua_settable_dispatcher, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__call");
	lua_pushcclosure(L, &class_rep::construct_lua_class_callback, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, &class_rep::static_class_gettable, 0);
	lua_rawset(L, -3);

	return detail::ref(L);
}

int luabind::detail::create_lua_instance_metatable(lua_State* L)
{
	lua_newtable(L);

	// just indicate that this really is a class and not just any user data
	lua_pushstring(L, "__luabind_class");
	lua_pushboolean(L, 1);
	lua_rawset(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcclosure(L, &class_rep::lua_class_gettable, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcclosure(L, &class_rep::lua_class_settable, 0);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	//lua_pushcclosure(L, detail::garbage_collector_s<detail::object_rep>::apply, 0);
	lua_pushcclosure(L, detail::object_rep::garbage_collector, 0);
	lua_rawset(L, -3);

	for (int i = 0; i < number_of_operators; ++i) add_operator_to_metatable(L, i);

	// store a reference to the instance-metatable in our class_rep
	return detail::ref(L);
}

void luabind::open(lua_State* L)
{
	// get the global class registry, or create one if it doesn't exist
	// (it's global within a lua state)
	detail::class_registry* r = 0;

	// If you hit this assert it's because you have called luabind::open() twice on
	// the same lua_State.
	assert((detail::class_registry::get_registry(L) == 0) && "you cannot call luabind::open() twice");

	lua_pushstring(L, "__luabind_classes");
	r = static_cast<detail::class_registry*>(lua_newuserdata(L, sizeof(detail::class_registry)));

	// set gc metatable
	lua_newtable(L);
	lua_pushstring(L, "__gc");
	lua_pushcclosure(L, detail::garbage_collector_s<detail::class_registry>::apply, 0);
	lua_settable(L, -3);
	lua_setmetatable(L, -2);

	new(r) detail::class_registry(L);
	lua_settable(L, LUA_REGISTRYINDEX);

	// add functions (class, cast etc...)
	lua_pushstring(L, "class");
	lua_pushcclosure(L, detail::create_class::stage1, 0);
	lua_settable(L, LUA_GLOBALSINDEX);
}

