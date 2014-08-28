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


#ifndef LUABIND_REF_HPP_INCLUDED
#define LUABIND_REF_HPP_INCLUDED

#include <luabind/config.hpp>

namespace luabind { namespace detail
{

	// based on luaL_ref from lauxlib.c in lua distribution
	inline int ref(lua_State *L)
	{
		int ref;
		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);  /* remove from stack */
			return LUA_REFNIL;  /* `nil' has a unique fixed reference */
		}

		lua_rawgeti(L, LUA_REGISTRYINDEX, 0);  /* get first free element */
		ref = (int)lua_tonumber(L, -1);  /* ref = t[0] */
		lua_pop(L, 1);  /* remove it from stack */
		if (ref != 0)
		{  /* any free element? */
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);  /* remove it from list */
			lua_rawseti(L, LUA_REGISTRYINDEX, 0);  /* (that is, t[0] = t[ref]) */
		}
		else
		{  /* no free elements */
			lua_pushliteral(L, "n");
			lua_pushvalue(L, -1);
			lua_rawget(L, LUA_REGISTRYINDEX);  /* get t.n */
			ref = (int)lua_tonumber(L, -1) + 1;  /* ref = t.n + 1 */
			lua_pop(L, 1);  /* pop t.n */
			lua_pushnumber(L, ref);
			lua_rawset(L, LUA_REGISTRYINDEX);  /* t.n = t.n + 1 */
		}
		lua_rawseti(L, LUA_REGISTRYINDEX, ref);
		return ref;
	}

	inline void unref(lua_State *L, int ref)
	{
		if (ref >= 0)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, 0);
			lua_rawseti(L, LUA_REGISTRYINDEX, ref);  /* t[ref] = t[0] */
			lua_pushnumber(L, ref);
			lua_rawseti(L, LUA_REGISTRYINDEX, 0);  /* t[0] = ref */
		}
	}

	inline void getref(lua_State* L, int r)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, r);
	}

}}

#endif // LUABIND_REF_HPP_INCLUDED

