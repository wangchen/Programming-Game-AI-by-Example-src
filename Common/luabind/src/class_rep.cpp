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
#include <utility>

using namespace luabind::detail;


#ifndef LUABIND_NO_ERROR_CHECKING

	std::string luabind::detail::get_overload_signatures_candidates(lua_State* L, std::vector<const overload_rep_base*>::iterator start, std::vector<const overload_rep_base*>::iterator end, std::string name)
	{
		std::string s;
		for (; start != end; ++start)
		{
			s += name;
			(*start)->get_signature(L, s);
			s += "\n";
		}
		return s;
	}

#endif


luabind::detail::class_rep::class_rep(LUABIND_TYPE_INFO type
	, const char* name
	, lua_State* L
	,  void(*destructor)(void*)
	,  void(*const_holder_destructor)(void*)
	, LUABIND_TYPE_INFO holder_type
	, LUABIND_TYPE_INFO const_holder_type
	, void*(*extractor)(void*)
	, const void*(*const_extractor)(void*)
	, void(*const_converter)(void*,void*)
	, void(*construct_holder)(void*,void*)
	, void(*construct_const_holder)(void*,void*)
	, int holder_size
	, int holder_alignment)

	: m_type(type)
	, m_holder_type(holder_type)
	, m_const_holder_type(const_holder_type)
	, m_extractor(extractor)
	, m_const_extractor(const_extractor)
	, m_const_converter(const_converter)
	, m_construct_holder(construct_holder)
	, m_construct_const_holder(construct_const_holder)
	, m_holder_size(holder_size)
	, m_holder_alignment(holder_alignment)
	, m_name(name)
	, m_table_ref(LUA_NOREF)
	, m_class_type(cpp_class)
	, m_destructor(destructor)
	, m_const_holder_destructor(const_holder_destructor)
	, m_operator_cache(0)
{
	assert(m_holder_alignment >= 1 && "internal error");

	class_registry* r = class_registry::get_registry(L);
	assert((r->cpp_class() != LUA_NOREF) && "you must call luabind::open()");

	detail::getref(L, r->cpp_class());
	lua_setmetatable(L, -2);

	lua_pushvalue(L, -1); // duplicate our user data
	m_self_ref = detail::ref(L); // pop one of them

	m_instance_metatable = r->cpp_instance();
}

luabind::detail::class_rep::class_rep(lua_State* L, const char* name)
	: m_type(LUABIND_INVALID_TYPE_INFO)
	, m_holder_type(LUABIND_INVALID_TYPE_INFO)
	, m_const_holder_type(LUABIND_INVALID_TYPE_INFO)
	, m_extractor(0)
	, m_const_extractor(0)
	, m_const_converter(0)
	, m_construct_holder(0)
	, m_construct_const_holder(0)
	, m_holder_size(0)
	, m_holder_alignment(1)
	, m_class_type(lua_class)
	, m_destructor(0)
	, m_const_holder_destructor(0)
	, m_operator_cache(0)
{
#ifndef LUABIND_DONT_COPY_STRINGS
	m_strings.push_back(detail::dup_string(name));
	m_name = m_strings.back();
#else
	m_name = name;
#endif
	lua_newtable(L);
	m_table_ref = detail::ref(L);

	class_registry* r = class_registry::get_registry(L);
	assert((r->cpp_class() != LUA_NOREF) && "you must call luabind::open()");

	detail::getref(L, r->lua_class());
	lua_setmetatable(L, -2);
	lua_pushvalue(L, -1); // duplicate our user data
	m_self_ref = detail::ref(L); // pop one of them

	m_instance_metatable = r->lua_instance();
}

luabind::detail::class_rep::~class_rep()
{
#ifndef LUABIND_DONT_COPY_STRINGS
	for (std::vector<char*>::iterator i = m_strings.begin(); 
			i != m_strings.end(); ++i)
	{
			delete[] *i;
	}
#endif
}

std::pair<void*,void*> 
luabind::detail::class_rep::allocate(lua_State* L) const
{
	const int overlap = sizeof(object_rep)&(m_holder_alignment-1);
	const int padding = overlap==0?0:m_holder_alignment-overlap;
	const int size = sizeof(object_rep) + padding + m_holder_size;

	char* mem = static_cast<char*>(lua_newuserdata(L, size));
	char* ptr = mem + sizeof(object_rep) + padding;

	return std::pair<void*,void*>(mem,ptr);
}

int luabind::detail::class_rep::gettable(lua_State* L)
{
	if (lua_isnil(L, 2))
	{
		lua_pushnil(L);
		return 1;
	}

	object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, 1));

	// we have to ignore the first argument since this may point to
	// a method that is not present in this class (but in a subclass)
	const char* key = lua_tostring(L, 2);

	if (key && !strcmp(key, "__ok"))
	{
		class_rep* crep = obj->crep();

		void* p = crep->extractor() ? crep->extractor()(obj->ptr())
			: obj->ptr();

		lua_pushboolean(L, p != 0);
		return 1;
	}

	std::map<const char*, method_rep, ltstr>::iterator i = m_methods.find(key);

	if (i != m_methods.end())
	{
		// the name is a method, return it
		lua_pushlightuserdata(L, &i->second);
		lua_pushcclosure(L, function_dispatcher, 1);
		return 1;
	}

	std::map<const char*, callback, ltstr>::iterator j = m_getters.find(key);
	if (j != m_getters.end())
	{
		// the name is a data member
		return j->second.func(L, j->second.pointer_offset);
	}

	lua_pushnil(L);
	return 1;
}

// called from the metamethod for __newindex
// the object pointer is passed on the lua stack
bool luabind::detail::class_rep::settable(lua_State* L)
{
	if (lua_isnil(L, 2))
	{
		return false;
	}

	// we have to ignore the first argument since this may point to
	// a method that is not present in this class (but in a subclass)
	const char* key = lua_tostring(L, 2);
	std::map<const char*, callback, ltstr>::iterator j = m_setters.find(key);
	if (j != m_setters.end())
	{
		// the name is a data member
		j->second.func(L, j->second.pointer_offset);
		return true;
	}

	return false; // false means that we don't have a member with the given name
}

 int class_rep::gettable_dispatcher(lua_State* L)
{
	object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, 1));
	return obj->crep()->gettable(L);
}

// this is called as __newindex metamethod on every instance of this class
 int luabind::detail::class_rep::settable_dispatcher(lua_State* L)
{
	object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, 1));

	bool success = obj->crep()->settable(L);

#ifndef LUABIND_NO_ERROR_CHECKING

	if (!success)
	{
		// this block is needed to make sure the std::string is destructed before
		// lua_error() is called
#ifdef BOOST_MSVC
		{
			// msvc has a bug which deletes the string twice, that's
			// why we have to create it on the heap
			std::string* msg = new std::string("cannot set attribute '");
			*msg += obj->crep()->m_name;
			*msg += ".";
			*msg += lua_tostring(L, -2);
			*msg += "'";
			lua_pushstring(L, msg->c_str());
			delete msg;
		}
#else
		{
			std::string msg = "cannot set attribute '";
			msg += obj->crep()->m_name;
			msg += ".";
			msg += lua_tostring(L, -2);
			msg += "'";
			lua_pushstring(L, msg.c_str());
		}
#endif
		lua_error(L);
	}

#endif

	return 0;
}


 int luabind::detail::class_rep::operator_dispatcher(lua_State* L)
{
	int id = static_cast<int>(lua_tonumber(L, lua_upvalueindex(1)));

	int operand_id = 0;

	object_rep* operand[2];
	for (int i = 0; i < 2; ++i)
		operand[i] = detail::is_class_object(L, i + 1);

	// we cannot compare the types here, we have to compare the pointers of the class_reps
	// since all lua-classes have the same type (LUABIND_INVALID_TYPE_INFO)
	if (operand[0] && operand[1])
		if (operand[0]->crep() == operand[1]->crep()) operand[1] = 0;

	std::vector<operator_callback>* overloads[2];
	for (int i = 0; i < 2; ++i)
		if (operand[i]) overloads[i] = &operand[i]->crep()->m_operators[id]; else overloads[i] = 0;

	std::size_t num_overloads[2];
	for (int i = 0; i < 2; ++i)
		if (overloads[i]) num_overloads[i] = overloads[i]->size(); else num_overloads[i] = 0;

	for (int i = 0; i < 2; ++i)
		if (operand[i] && operand[i]->crep()->get_class_type() == class_rep::lua_class)
		{
/*			// if this is a lua class we have to
			// look in its table to see if there's
			// any overload of this operator
			detail::getref(L, operand[i]->crep()->table_ref());
			lua_pushstring(L, get_operator_name(id));
			lua_rawget(L, -2);
			// if we have tha operator, set num_overloads to 1
			if (lua_isfunction(L, -1)) num_overloads[i] = 1;
			lua_pop(L, 2);*/
			
			if (operand[i]->crep()->has_operator_in_lua(L, id))
				num_overloads[i] = 1;
		}

	bool ambiguous = false;
	int match_index = -1;
	int min_match = std::numeric_limits<int>::max();

#ifdef LUABIND_NO_ERROR_CHECKING

	if (num_overloads[0] == 1 && num_overloads[1] == 0)
	{
		operand_id = 0;
		match_index = 0;
	}
	else if (num_overloads[0] == 0 && num_overloads[1] == 1)
	{
		operand_id = 1;
		match_index = 0;
	}
	else
	{

#endif

		int num_params = lua_gettop(L);

		// have look at the right operand.
		// if the right operand is a class and
		// not the same class as this, we have to
		// try to match it's operators too	
		for (int i = 0; i < 2; ++i)
		{
			if (num_overloads[i])
			{
				if (operand[i]->crep()->get_class_type() == class_rep::lua_class)
				{
					// if this is a lua class
					// and num_overloads is > 0
					// it means that it has implemented
					// this operator. Set match_index to
					// 0 to signal that this operand has
					// an overload, but leave the min_match
					// at int-max to mark it as a last resort
					operand_id = i;
					if (match_index == -1) match_index = 0;
				}
				else if (find_best_match(
					L
					, &overloads[i]->front()
					, overloads[i]->size()
					, sizeof(operator_callback)
					, ambiguous
					, min_match
					, match_index
					, num_params))
				{
					operand_id = i;
				}
			}
		}


#ifdef LUABIND_NO_ERROR_CHECKING

	}

#else

	if (match_index == -1)
	{
		// this block is needed to make sure the std::string is destructed before
		// lua_error() is called
		{
			std::string msg = "no operator ";
			msg += get_operator_symbol(id);
			msg += " matched the arguments (";
			msg += stack_content_by_name(L, 1);
			msg += ")\ncandidates are:\n";

			for (int i = 0; i < 2; ++i)
			{
				if (overloads[i])
				{
					msg += get_overload_signatures(
							L
							, overloads[i]->begin()
							, overloads[i]->end()
							, get_operator_symbol(id));
				}
				else
				{
					// if num_overloads is > 0 it would mean that this is
					// a lua class with this operator overloaded. And if
					// that's the case, it should always match (and if an
					// operator matches, we never come here).
					assert(num_overloads[i] == 0 && "internal error");
				}
			}

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}
	else if (ambiguous)
	{
		// this block is needed to make sure the std::string is destructed before
		// lua_error() is called
		{
			std::string msg = "call of overloaded operator ";
			msg += get_operator_symbol(id);
			msg += " (";
			msg += stack_content_by_name(L, 1);
			msg += ")' is ambiguous\nnone of the overloads have a best conversion:\n";

			std::vector<const overload_rep_base*> candidates;
			if (overloads[0])
				find_exact_match(L, &overloads[0]->front(), overloads[0]->size(), sizeof(operator_callback), min_match, num_params, candidates);

			if (overloads[1])
				find_exact_match(L, &overloads[1]->front(), overloads[1]->size(), sizeof(operator_callback), min_match, num_params, candidates);

			msg += get_overload_signatures_candidates(L, candidates.begin(), candidates.end(), get_operator_symbol(id));

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

#endif

	if (operand[operand_id]->crep()->get_class_type() == class_rep::lua_class)
	{
		detail::getref(L, operand[operand_id]->crep()->table_ref());
		lua_pushstring(L, get_operator_name(id));
		lua_rawget(L, -2);
		lua_insert(L, -4); // move the function to the bottom
		lua_pop(L, 1); // remove the table
		lua_call(L, 2, 1);
		return 1;
	}
	else
	{
		return (*overloads[operand_id])[match_index].call(L);
	}
}

// this is called as metamethod __call on the class_rep.
 int luabind::detail::class_rep::constructor_dispatcher(lua_State* L)
{
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, 1));
	construct_rep* rep = &crep->m_constructor;

	bool ambiguous = false;
	int match_index = -1;
	int min_match = std::numeric_limits<int>::max();
	bool found;

#ifdef LUABIND_NO_ERROR_CHECKING

	if (rep->overloads.size() == 1)
	{
		match_index = 0;
	}
	else
	{

#endif

		int num_params = lua_gettop(L) - 1;
		found = find_best_match(L, &rep->overloads.front(), rep->overloads.size(), sizeof(construct_rep::overload_t), ambiguous, min_match, match_index, num_params);

#ifdef LUABIND_NO_ERROR_CHECKING
	}

#else

	if (!found)
	{
		// this block is needed to make sure the std::string is destructed before
		// lua_error() is called
		{
			std::string msg = "no constructor of '";
			msg += crep->name();
			msg += "' matched the arguments (";
			msg += stack_content_by_name(L, 2);
			msg += ")\n candidates are:\n";

			msg += get_overload_signatures(L, rep->overloads.begin(), rep->overloads.end(), crep->name());

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}
	else if (ambiguous)
	{
		// this block is needed to make sure the std::string is destructed before
		// lua_error() is called
		{
			std::string msg = "call of overloaded constructor '";
			msg += crep->m_name;
			msg +=  "(";
			msg += stack_content_by_name(L, 2);
			msg += ")' is ambiguous\nnone of the overloads have a best conversion:\n";

			std::vector<const overload_rep_base*> candidates;
			find_exact_match(L, &rep->overloads.front(), rep->overloads.size(), sizeof(construct_rep::overload_t), min_match, num_params, candidates);
			msg += get_overload_signatures_candidates(L, candidates.begin(), candidates.end(), crep->name());

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

#endif

#ifndef LUABIND_NO_EXCEPTIONS

	try
	{

#endif

		void* object_ptr = rep->overloads[match_index].construct(L);

		void* obj_rep;
		void* held;

		boost::tie(obj_rep,held) = crep->allocate(L);

		if (crep->has_holder())
		{
			crep->m_construct_holder(held, object_ptr);
			object_ptr = held;
		}
		new(obj_rep) object_rep(object_ptr, crep, object_rep::owner, crep->destructor());

		detail::getref(L, crep->m_instance_metatable);
		lua_setmetatable(L, -2);
		return 1;

#ifndef LUABIND_NO_EXCEPTIONS

	}

	catch(const std::exception& e)
	{
		lua_pushstring(L, e.what());
	}
	catch(const char* s)
	{
		lua_pushstring(L, s);
	}
	catch(...)
	{
		{
			std::string msg = crep->name();
			msg += "() threw an exception";
			lua_pushstring(L, msg.c_str());
		}
	}

	// we can only reach this line if an exception was thrown
	lua_error(L);
	return 0; // will never be reached

#endif

}

// TODO: remove
/*
 int luabind::detail::class_rep::implicit_cast(const class_rep* from, const class_rep* to, int& pointer_offset)
{
	int offset = 0;
	if (LUABIND_TYPE_INFO_EQUAL(from->type(), to->type())) return 0;

	for (std::vector<class_rep::base_info>::const_iterator i = from->bases().begin(); i != from->bases().end(); ++i)
	{
		int steps = implicit_cast(i->base, to, offset);
		pointer_offset = offset + i->pointer_offset;
		if (steps >= 0) return steps + 2;
	}
	return -1;
}
*/


// the functions dispatcher assumes the following:
// there is one upvalue that points to the method_rep that this dispatcher is to call
// the first parameter on the lua stack is an object_rep that points to the object the
// call is being made on
int luabind::detail::class_rep::function_dispatcher(lua_State* L)
{
	method_rep* rep = static_cast<method_rep*>(lua_touserdata(L, lua_upvalueindex(1)));
	object_rep* obj = reinterpret_cast<object_rep*>(lua_touserdata(L, 1));

#ifndef LUABIND_NO_ERROR_CHECKING

	if (is_class_object(L, 1) == 0)
	{
		{
			std::string msg = "No self reference given as first parameter to member function '";
			msg += rep->crep->name();
			msg += ":";
			msg += rep->name;
			msg += "'. Have you used '.' instead of ':'?";

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

	int p;
	if (implicit_cast(obj->crep(), rep->crep->type(), p) < 0)
	{
		{
			std::string msg = "invalid self reference given to '";
			msg += rep->crep->name();
			msg += ":";
			msg += rep->name;
			msg += "'";
			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

#endif

	bool ambiguous = false;
	int match_index = -1;
	int min_match = std::numeric_limits<int>::max();
	bool found;

#ifdef LUABIND_NO_ERROR_CHECKING
	if (rep->overloads().size() == 1)
	{
		match_index = 0;
	}
	else
	{
#endif

		int num_params = lua_gettop(L) - 1;
		found = find_best_match(L, &rep->overloads().front(), rep->overloads().size(), sizeof(overload_rep), ambiguous, min_match, match_index, num_params);

#ifdef LUABIND_NO_ERROR_CHECKING

	}

#else

	if (!found)
	{
		{
			std::string msg = "no overload of  '";
			msg += rep->crep->name();
			msg += ":";
			msg += rep->name;
			msg += "' matched the arguments (";
			msg += stack_content_by_name(L, 2);
			msg += ")\ncandidates are:\n";

			std::string function_name;
			function_name += rep->crep->name();
			function_name += ":";
			function_name += rep->name;

			msg += get_overload_signatures(L, rep->overloads().begin(), rep->overloads().end(), function_name);

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}
	else if (ambiguous)
	{
		{
			std::string msg = "call of overloaded  '";
			msg += rep->crep->name();
			msg += ":";
			msg += rep->name;
			msg += "(";
			msg += stack_content_by_name(L, 2);
			msg += ")' is ambiguous\nnone of the overloads have a best conversion:\n";

			std::vector<const overload_rep_base*> candidates;
			find_exact_match(L, &rep->overloads().front(), rep->overloads().size(), sizeof(overload_rep), min_match, num_params, candidates);

			std::string function_name;
			function_name += rep->crep->name();
			function_name += ":";
			function_name += rep->name;

			msg += get_overload_signatures_candidates(L, candidates.begin(), candidates.end(), function_name);

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

#endif

#ifndef LUABIND_NO_EXCEPTIONS

	try
	{

#endif

		const overload_rep& o = rep->overloads()[match_index];
		return o.call(L, *obj);

#ifndef LUABIND_NO_EXCEPTIONS

	}
	catch(const std::exception& e)
	{
		lua_pushstring(L, e.what());
	}
	catch (const char* s)
	{
		lua_pushstring(L, s);
	}
	catch(...)
	{
		std::string msg = rep->crep->name();
		msg += ":";
		msg += rep->name;
		msg += "() threw an exception";
		lua_pushstring(L, msg.c_str());
	}
	// we can only reach this line if an exception was thrown
	lua_error(L);
	return 0; // will never be reached

#endif
			
}

void luabind::detail::class_rep::add_base_class(const luabind::detail::class_rep::base_info& binfo)
{
	// If you hit this assert you are deriving from a type that is not registered
	// in lua. That is, in the class_<> you are giving a baseclass that isn't registered.
	// Please note that if you don't need to have access to the base class or the
	// conversion from the derived class to the base class, you don't need
	// to tell luabind that it derives.
	assert(binfo.base && "You cannot derive from an unregistered type");

	class_rep* bcrep = binfo.base;

	// import all functions from the base
	for (std::map<const char*, method_rep, ltstr>::const_iterator i = bcrep->m_methods.begin();
			i != bcrep->m_methods.end(); ++i)
	{
		// If we would assume that our base class will not be garbage collected until 
		// this class is collected, we wouldn't had to copy these strings.
#ifndef LUABIND_DONT_COPY_STRINGS
		m_strings.push_back(dup_string(i->first));
		method_rep& m = m_methods[m_strings.back()];
#else
		method_rep& m = m_methods[i->first];
#endif
		m.name = i->first;
		m.crep = this;

		for (std::vector<overload_rep>::const_iterator j = i->second.overloads().begin(); 
				j != i->second.overloads().end(); ++j)
		{
			overload_rep o = *j;
			o.add_offset(binfo.pointer_offset);
			m.add_overload(o);
		}
	}

	// import all getters from the base
	for (std::map<const char*, callback, ltstr>::const_iterator i = bcrep->m_getters.begin(); 
			i != bcrep->m_getters.end(); ++i)
	{
#ifndef LUABIND_DONT_COPY_STRINGS
		m_strings.push_back(dup_string(i->first));
		callback& m = m_getters[m_strings.back()];
#else
		callback& m = m_getters[i->first];
#endif
		m.pointer_offset = i->second.pointer_offset + binfo.pointer_offset;
		m.func = i->second.func;
	}

	// import all setters from the base
	for (std::map<const char*, callback, ltstr>::const_iterator i = bcrep->m_setters.begin(); 
			i != bcrep->m_setters.end(); ++i)
	{
#ifndef LUABIND_DONT_COPY_STRINGS
		// TODO: optimize this by not copying the string if it already exists in m_setters.
		// This goes for m_getters, m_static_constants and m_functions too. Both here
		// in add_base() and in the add_function(), add_getter() ... functions.
		m_strings.push_back(dup_string(i->first));
		callback& m = m_setters[m_strings.back()];
#else
		callback& m = m_setters[i->first];
#endif
		m.pointer_offset = i->second.pointer_offset + binfo.pointer_offset;
		m.func = i->second.func;
	}

	// import all static constants
	for (std::map<const char*, int, ltstr>::const_iterator i = bcrep->m_static_constants.begin(); 
			i != bcrep->m_static_constants.end(); ++i)
	{
#ifndef LUABIND_DONT_COPY_STRINGS
		m_strings.push_back(dup_string(i->first));
		int& v = m_static_constants[m_strings.back()];
#else
		int& v = m_static_constants[i->first];
#endif
		v = i->second;
	}

	// import all operators
	for (int i = 0; i < number_of_operators; ++i)
	{
		for (std::vector<operator_callback>::const_iterator j = bcrep->m_operators[i].begin(); 
				j != bcrep->m_operators[i].end(); ++j)
			m_operators[i].push_back(*j);
	}

	// also, save the baseclass info to be used for typecasts
	m_bases.push_back(binfo);
}
/*
void luabind::detail::class_rep::add_function(const char* name, const overload_rep& o)
{

#ifdef LUABIND_DONT_COPY_STRINGS
	detail::method_rep& method = m_methods[name];
	method.name = name;
#else
	m_strings.push_back(dup_string(name));
	detail::method_rep& method = m_methods[m_strings.back()];
	method.name = m_strings.back();
#endif

	method.add_overload(o);
	method.crep = this;
}

void luabind::detail::class_rep::add_getter(const char* name, const boost::function2<int, lua_State*, int>& g)
{
	callback c;
	c.func = g;
	c.pointer_offset = 0;
#ifndef LUABIND_DONT_COPY_STRINGS
	m_strings.push_back(dup_string(name));
	m_getters[m_strings.back()] = c;
#else
	m_getters[name] = c;
#endif
}

void luabind::detail::class_rep::add_setter(const char* name, const boost::function2<int, lua_State*, int>& s)
{
	callback c;
	c.func = s;
	c.pointer_offset = 0;
#ifndef LUABIND_DONT_COPY_STRINGS
	m_strings.push_back(dup_string(name));
	m_setters[m_strings.back()] = c;
#else
	m_setters[name] = c;
#endif
}

#ifndef LUABIND_NO_ERROR_CHECKING
void luabind::detail::class_rep::add_operator(lua_State*, int op_id,  int(*func)(lua_State*), int(*matcher)(lua_State*), void(*sig)(lua_State*, std::string&), int arity)
#else
void luabind::detail::class_rep::add_operator(lua_State*, int op_id,  int(*func)(lua_State*), int(*matcher)(lua_State*), int arity)
#endif
{
	operator_callback o;
	o.set_fun(func);
	o.set_match_fun(matcher);
	o.set_arity(arity);

#ifndef LUABIND_NO_ERROR_CHECKING

	o.set_sig_fun(sig);

#endif
	m_operators[op_id].push_back(o);
}

void luabind::detail::class_rep::add_static_constant(const char* name, int val)
{
#ifndef LUABIND_DONT_COPY_STRINGS
	m_strings.push_back(dup_string(name));
	m_static_constants[m_strings.back()] = val;
#else
	m_static_constants[name] = val;
#endif
}
*/
 int luabind::detail::class_rep::super_callback(lua_State* L)
{
	int args = lua_gettop(L);
		
	object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, lua_upvalueindex(2)));
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, lua_upvalueindex(1)));
	class_rep* base = crep->bases()[0].base;

	if (base->get_class_type() == class_rep::lua_class)
	{
		if (base->bases().empty())
		{
			obj->set_flags(obj->flags() & ~object_rep::call_super);

			lua_pushstring(L, "super");
			lua_pushnil(L);
			lua_settable(L, LUA_GLOBALSINDEX);
		}
		else
		{
			lua_pushstring(L, "super");
			lua_pushlightuserdata(L, base);
			lua_pushvalue(L, lua_upvalueindex(2));
			lua_pushcclosure(L, super_callback, 2);
			lua_settable(L, LUA_GLOBALSINDEX);
		}

		detail::getref(L, base->table_ref());
		lua_pushstring(L, "__init");
		lua_gettable(L, -2);
		lua_insert(L, 1);
		lua_pop(L, 1);

		lua_pushvalue(L, lua_upvalueindex(2));
		lua_insert(L, 2);

		lua_call(L, args + 1, 0);

		// TODO: instead of clearing the global variable "super"
		// store it temporarily in the registry. maybe we should
		// have some kind of warning if the super global is used?
		lua_pushstring(L, "super");
		lua_pushnil(L);
		lua_settable(L, LUA_GLOBALSINDEX);
	}
	else
	{
		obj->set_flags(obj->flags() & ~object_rep::call_super);

		// we need to push some garbage at index 1 to make the construction work
		lua_pushboolean(L, 1);
		lua_insert(L, 1);

		construct_rep* rep = &base->m_constructor;

		bool ambiguous = false;
		int match_index = -1;
		int min_match = std::numeric_limits<int>::max();
		bool found;
			
#ifdef LUABIND_NO_ERROR_CHECKING

		if (rep->overloads.size() == 1)
		{
			match_index = 0;
		}
		else
		{

#endif

			int num_params = lua_gettop(L) - 1;
			found = find_best_match(L, &rep->overloads.front(), rep->overloads.size(), sizeof(construct_rep::overload_t), ambiguous, min_match, match_index, num_params);

#ifdef LUABIND_NO_ERROR_CHECKING

		}

#else
				
		if (!found)
		{
			{
				std::string msg = "no constructor of '";
				msg += base->m_name;
				msg += "' matched the arguments (";
				msg += stack_content_by_name(L, 2);
				msg += ")";
				lua_pushstring(L, msg.c_str());
			}
			lua_error(L);
		}
		else if (ambiguous)
		{
			{
				std::string msg = "call of overloaded constructor '";
				msg += base->m_name;
				msg +=  "(";
				msg += stack_content_by_name(L, 2);
				msg += ")' is ambiguous";
				lua_pushstring(L, msg.c_str());
			}
			lua_error(L);
		}

			// TODO: should this be a warning or something?
/*
			// since the derived class is a lua class
			// it may have reimplemented virtual functions
			// therefore, we have to instantiate the Basewrapper
			// if there is no basewrapper, throw a run-time error
			if (!rep->overloads[match_index].has_wrapped_construct())
			{
				{
					std::string msg = "Cannot derive from C++ class '";
					msg += base->name();
					msg += "'. It does not have a wrapped type";
					lua_pushstring(L, msg.c_str());
				}
				lua_error(L);
			}
*/
#endif

#ifndef LUABIND_NO_EXCEPTIONS

		try
		{

#endif

			if (!rep->overloads[match_index].has_wrapped_construct())
			{
				// if the type doesn't have a wrapped type, use the ordinary constructor
				obj->set_object(rep->overloads[match_index].construct(L));
			}
			else
			{
				// get reference to lua object
				lua_pushvalue(L, lua_upvalueindex(2));
				int ref = detail::ref(L);
				obj->set_object(rep->overloads[match_index].construct_wrapped(L, ref));
			}
			// TODO: is the wrapped type destructed correctly?
			// it should, since the destructor is either the wrapped type's
			// destructor or the base type's destructor, depending on wether
			// the type has a wrapped type or not.
			obj->set_destructor(base->destructor());
			return 0;

#ifndef LUABIND_NO_EXCEPTIONS

		}
		catch(const std::exception& e)
		{
			lua_pushstring(L, e.what());
		}
		catch(const char* s)
		{
			lua_pushstring(L, s);
		}
		catch(...)
		{
			std::string msg = base->m_name;
			msg += "() threw an exception";
			lua_pushstring(L, msg.c_str());
		}
		// can only be reached if an exception was thrown
		lua_error(L);
#endif
	}

	return 0;

}



 int luabind::detail::class_rep::lua_settable_dispatcher(lua_State* L)
{
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, 1));
	detail::getref(L, crep->m_table_ref);
	lua_replace(L, 1);
	lua_rawset(L, -3);

	crep->m_operator_cache = 0; // invalidate cache
	
	return 0;
}

 int luabind::detail::class_rep::construct_lua_class_callback(lua_State* L)
{
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, 1));

	int args = lua_gettop(L);

	// lua stack: crep <arguments>

	lua_newtable(L);
	int ref = detail::ref(L);

	bool has_bases = !crep->bases().empty();
		
	if (has_bases)
	{
		lua_pushstring(L, "super");
		lua_pushvalue(L, 1); // crep
	}

	// lua stack: crep <arguments> "super" crep
	// or
	// lua stack: crep <arguments>

	// if we have a baseclass we set the flag to say that the super has not yet been called
	// we will use this flag later to check that it actually was called from __init()
	int flags = object_rep::lua_class | object_rep::owner | (has_bases ? object_rep::call_super : 0);

	void* obj_ptr = lua_newuserdata(L, sizeof(object_rep));
	new(obj_ptr) object_rep(crep, flags, ref);

	detail::getref(L, crep->metatable_ref());
	lua_setmetatable(L, -2);

	// lua stack: crep <arguments> "super" crep obj_ptr
	// or
	// lua stack: crep <arguments> obj_ptr

	if (has_bases)	lua_pushvalue(L, -1); // obj_ptr
	lua_replace(L, 1); // obj_ptr

	// lua stack: obj_ptr <arguments> "super" crep obj_ptr
	// or
	// lua stack: obj_ptr <arguments>

	if (has_bases)
	{
		lua_pushcclosure(L, super_callback, 2);
		// lua stack: crep <arguments> "super" function
		lua_settable(L, LUA_GLOBALSINDEX);
	}

	// lua stack: crep <arguments>

	lua_pushvalue(L, 1);
	lua_insert(L, 1);

	detail::getref(L, crep->table_ref());
	lua_pushstring(L, "__init");
	lua_gettable(L, -2);

#ifndef LUABIND_NO_ERROR_CHECKING

	// TODO: should this be a run-time error?
	// maybe the default behavior should be to just call
	// the base calss' constructor. We should register
	// the super callback funktion as __init
	if (!lua_isfunction(L, -1))
	{
		{
			std::string msg = crep->name();
			msg += ":__init is not defined";
			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

#endif

	lua_insert(L, 2); // function first on stack
	lua_pop(L, 1);
	// TODO: lua_call may invoke longjump! make sure we don't have any memory leaks!
	// we don't have any stack objects here
	lua_call(L, args, 0);

#ifndef LUABIND_NO_ERROR_CHECKING

	object_rep* obj = static_cast<object_rep*>(obj_ptr);
	if (obj->flags() & object_rep::call_super)
	{
		lua_pushstring(L, "derived class must call super on base");
		lua_error(L);
	}

#endif

	return 1;
}

// called from the metamethod for __index
// obj is the object pointer
 int luabind::detail::class_rep::lua_class_gettable(lua_State* L)
{
	object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, 1));
	class_rep* crep = obj->crep();

#ifndef LUABIND_NO_ERROR_CHECKING

	if (obj->flags() & object_rep::call_super)
	{
		lua_pushstring(L, "derived class must call super on base");
		lua_error(L);
	}

#endif

	// we have to ignore the first argument since this may point to
	// a method that is not present in this class (but in a subclass)
	const char* key = lua_tostring(L, 2);

	if (key && !strcmp(key, "__ok"))
	{
		class_rep* crep = obj->crep();

		void* p = crep->extractor() ? crep->extractor()(obj->ptr())
			: obj->ptr();

		lua_pushboolean(L, p != 0);
		return 1;
	}
	
	detail::getref(L, obj->lua_table_ref());
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);

	if (!lua_isnil(L, -1)) 
	{
		lua_remove(L, -2); // remove table
		return 1;
	}

	lua_pop(L, 2);

	detail::getref(L, crep->table_ref());
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);

	if (!lua_isnil(L, -1)) 
	{
		lua_remove(L, -2); // more table
		return 1;
	}

	lua_pop(L, 2);

	if (lua_isnil(L, 2))
	{
		lua_pushnil(L);
		return 1;
	}

	std::map<const char*, method_rep, ltstr>::iterator i = crep->m_methods.find(key);
	if (i != crep->m_methods.end())
	{
		// the name is a method, return it
		lua_pushlightuserdata(L, &i->second);
		lua_pushcclosure(L, class_rep::function_dispatcher, 1);
		return 1;
	}

	std::map<const char*, class_rep::callback, ltstr>::iterator j = crep->m_getters.find(key);
	if (j != crep->m_getters.end())
	{
		// the name is a data member
		return j->second.func(L, j->second.pointer_offset);
	}

	lua_pushnil(L);
	return 1;
}

// called from the metamethod for __newindex
// obj is the object pointer
 int luabind::detail::class_rep::lua_class_settable(lua_State* L)
{
	object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, 1));
	class_rep* crep = obj->crep();

#ifndef LUABIND_NO_ERROR_CHECKING

	if (obj->flags() & object_rep::call_super)
	{
		// this block makes sure the std::string is destructed
		// before lua_error is called
		{
			std::string msg = "derived class '";
			msg += crep->name();
			msg += "'must call super on base";
			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}

#endif

	// we have to ignore the first argument since this may point to
	// a method that is not present in this class (but in a subclass)
	const char* key = lua_tostring(L, 2);
	std::map<const char*, class_rep::callback, ltstr>::iterator j = crep->m_setters.find(key);

	if (j == crep->m_setters.end())
	{
		std::map<const char*, class_rep::callback, ltstr>::iterator k = crep->m_getters.find(key);

#ifndef LUABIND_NO_ERROR_CHECKING

		if (k != crep->m_getters.end())
		{
			{
				std::string msg = "cannot set property '";
				msg += crep->name();
				msg += ".";
				msg += key;
				msg += "', because it's read only";
				lua_pushstring(L, msg.c_str());
			}
			lua_error(L);
		}

#endif

		detail::getref(L, obj->lua_table_ref());
		lua_replace(L, 1);
		lua_settable(L, 1);
	}
	else
	{
		// the name is a data member
		j->second.func(L, j->second.pointer_offset);
	}

	return 0;
}

 int luabind::detail::class_rep::static_class_gettable(lua_State* L)
{
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, 1));

	if (crep->get_class_type() == class_rep::lua_class)
	{
		detail::getref(L, crep->m_table_ref);
		lua_pushvalue(L, 2);
		lua_gettable(L, -2);
		if (!lua_isnil(L, -1)) return 1;
		else lua_pop(L, 2);
	}

	const char* key = lua_tostring(L, 2);

	std::map<const char*, method_rep, ltstr>::iterator i = crep->m_methods.find(key);
	if (i != crep->m_methods.end())
	{
		// the name is a method, return it
		lua_pushlightuserdata(L, &i->second);
		lua_pushcclosure(L, class_rep::function_dispatcher, 1);
		return 1;
	}

#ifndef LUABIND_NO_ERROR_CHECKING

	std::map<const char*, int, ltstr>::const_iterator j = crep->m_static_constants.find(key);

	if (j != crep->m_static_constants.end())
	{
		lua_pushnumber(L, j->second);
		return 1;
	}

	{
		std::string msg = "no static '";
		msg += key;
		msg += "' in class '";
		msg += crep->name();
		msg += "'";
		lua_pushstring(L, msg.c_str());
	}
	lua_error(L);

#endif

	return 0;
}

bool luabind::detail::is_class_rep(lua_State* L, int index)
{
	if (lua_getmetatable(L, index) == 0) return false;

	lua_pushstring(L, "__luabind_classrep");
	lua_gettable(L, -2);
	if (lua_toboolean(L, -1))
	{
		lua_pop(L, 2);
		return true;
	}

	lua_pop(L, 2);
	return false;
}

void luabind::detail::finalize(lua_State* L, class_rep* crep)
{
	if (crep->get_class_type() != class_rep::lua_class) return;

	detail::getref(L, crep->table_ref());
	lua_pushstring(L, "__finalize");
	lua_gettable(L, -2);

	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
	}
	else
	{
		lua_pushvalue(L, -2);
		lua_call(L, 1, 0);
	}

	for (std::vector<class_rep::base_info>::const_iterator 
			i = crep->bases().begin(); i != crep->bases().end(); ++i)
	{
		if (i->base) finalize(L, i->base);
	}
}

void* luabind::detail::class_rep::convert_to(LUABIND_TYPE_INFO target_type, const object_rep* obj, void* target_memory) const
{
	// TODO: since this is a member function, we don't have to use the accesor functions for
	// the types and the extractor

	int steps = 0;
	int offset = 0;
	if (!(LUABIND_TYPE_INFO_EQUAL(obj->crep()->holder_type(), target_type))
		&& !(LUABIND_TYPE_INFO_EQUAL(obj->crep()->const_holder_type(), target_type)))
	{
		steps = implicit_cast(this, target_type, offset);
	}

	// should never be called with a type that can't be cast
	assert((steps >= 0) && "internal error, please report");

	if (LUABIND_TYPE_INFO_EQUAL(target_type, holder_type()))
	{
		// if the type we are trying to convert to is the holder_type
		// it means that his crep has a holder_type (since it would have
		// been invalid otherwise, and T cannot be invalid). It also means
		// that we need no conversion, since the holder_type is what the
		// object points to.
		return obj->ptr();
	}

	if (LUABIND_TYPE_INFO_EQUAL(target_type, const_holder_type()))
	{
		if (obj->flags() & object_rep::constant)
		{
			// we are holding a constant
			return obj->ptr();
		}
		else
		{
			// we are holding a non-constant, we need to convert it
			// to a const_holder.
			m_const_converter(obj->ptr(), target_memory);
			return target_memory;
		}
	}

	void* raw_pointer;

	if (has_holder())
	{
		// this means that we have a holder type where the
		// raw-pointer needs to be extracted
		raw_pointer = extractor()(obj->ptr());
	}
	else
	{
		raw_pointer = obj->ptr();
	}

	return static_cast<char*>(raw_pointer) + offset;
}

void class_rep::cache_operators(lua_State* L)
{
	m_operator_cache = 0x1;

	for (int i = 0; i < number_of_operators; ++i)
	{
		getref(L, table_ref());
		lua_pushstring(L, get_operator_name(i));
		lua_rawget(L, -2);

		if (lua_isfunction(L, -1)) m_operator_cache |= 1 << (i + 1);

		lua_pop(L, 2);
	}
}

bool class_rep::has_operator_in_lua(lua_State* L, int id)
{
	if ((m_operator_cache & 0x1) == 0)
		cache_operators(L);

	const int mask = 1 << (id + 1);

	return m_operator_cache & mask;
}

