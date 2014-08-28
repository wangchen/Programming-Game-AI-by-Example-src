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

#ifndef LUABIND_OVERLOAD_REP_BASE_HPP_INCLUDED
#define LUABIND_OVERLOAD_REP_BASE_HPP_INCLUDED

#include <luabind/config.hpp>

namespace luabind { namespace detail
{
	// this class represents a specific overload of a member-function.
	struct overload_rep_base
	{
		typedef int(*match_ptr)(lua_State*);
		typedef void(*get_sig_ptr)(lua_State*, std::string&);

		inline int match(lua_State* L, int num_params) const { if (num_params != m_arity) return -1; return m_match_fun(L); }
		inline void set_match_fun(match_ptr f) { m_match_fun = f; }

#ifndef LUABIND_NO_ERROR_CHECKING
		inline void get_signature(lua_State* L, std::string& s) const { m_get_signature_fun(L, s); }
		inline void set_sig_fun(get_sig_ptr f) { m_get_signature_fun = f; }
#endif

	protected:

#ifndef LUABIND_NO_ERROR_CHECKING
		get_sig_ptr m_get_signature_fun;
#endif

		match_ptr m_match_fun;
		int m_arity;
	};

}} // namespace luabind::detail

#endif // LUABIND_OVERLOAD_REP_BASE_HPP_INCLUDED
