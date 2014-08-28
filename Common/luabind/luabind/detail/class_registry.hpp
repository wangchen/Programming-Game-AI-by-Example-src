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


#ifndef LUABIND_CLASS_REGISTRY_HPP_INCLUDED
#define LUABIND_CLASS_REGISTRY_HPP_INCLUDED

#include <luabind/config.hpp>
#include <string>

namespace luabind { namespace detail
{
	class class_rep;

	std::string stack_content_by_name(lua_State* L, int start_index);
	int create_cpp_class_metatable(lua_State* L);
	int create_cpp_instance_metatable(lua_State* L);
	int create_lua_class_metatable(lua_State* L);
	int create_lua_instance_metatable(lua_State* L);

	struct class_registry
	{
		class_registry(lua_State* L)
			: m_cpp_instance_metatable(create_cpp_instance_metatable(L))
			, m_cpp_class_metatable(create_cpp_class_metatable(L))
			, m_lua_instance_metatable(create_lua_instance_metatable(L))
			, m_lua_class_metatable(create_lua_class_metatable(L))
		{}

		static inline class_registry* get_registry(lua_State* L)
		{

#ifdef LUABIND_NOT_THREADSAFE

			// if we don't have to be thread safe, we can keep a
			// chache of the class_registry pointer without the
			// need of a mutex
			static lua_State* cache_key = 0;
			static class_registry* registry_cache = 0;
			if (cache_key == L) return registry_cache;

#endif

			lua_pushstring(L, "__luabind_classes");
			lua_gettable(L, LUA_REGISTRYINDEX);
			class_registry* p = static_cast<class_registry*>(lua_touserdata(L, -1));
			lua_pop(L, 1);

#ifdef LUABIND_NOT_THREADSAFE

			cache_key = L;
			registry_cache = p;

#endif

			return p;
		}

		int cpp_instance() const { return m_cpp_instance_metatable; }
		int cpp_class() const { return m_cpp_class_metatable; }

		int lua_instance() const { return m_lua_instance_metatable; }
		int lua_class() const { return m_lua_class_metatable; }

		void add_class(LUABIND_TYPE_INFO info, class_rep* crep)
		{
			// class is already registered
			assert((m_classes.find(info) == m_classes.end()) && "you are trying to register a class twice");
			m_classes[info] = crep;
		}

		class_rep* find_class(LUABIND_TYPE_INFO info)
		{
			std::map<LUABIND_TYPE_INFO, class_rep*>::iterator i = m_classes.find(info);
			if (i == m_classes.end()) return 0; // the type is not registered
			return i->second;
		}

	private:

		std::map<LUABIND_TYPE_INFO, class_rep*> m_classes;

		// this is a lua reference that points to the lua table
		// that is to be used as meta table for all C++ class 
		// instances. It is a kind of v-table.
		int m_cpp_instance_metatable;

		// this is a lua reference to the metatable to be used
		// for all classes defined in C++.
		int m_cpp_class_metatable;

		// this is a lua reference that points to the lua table
		// that is to be used as meta table for all lua class
		// instances. It is a kind of v-table.
		int m_lua_instance_metatable;

		// this is a lua reference to the metatable to be used
		// for all classes defined in lua
		int m_lua_class_metatable;

	};

}}

#endif // LUABIND_CLASS_REGISTRY_HPP_INCLUDED

