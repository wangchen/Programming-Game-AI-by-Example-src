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

#ifndef LUABIND_OVERLOAD_REP_IMPL_HPP_INCLUDED
#define LUABIND_OVERLOAD_REP_IMPL_HPP_INCLUDED

#include <luabind/detail/overload_rep.hpp>

namespace luabind { namespace detail
{
	inline int overload_rep::call(lua_State* L, const object_rep& o) const 
	{ 
		const class_rep* crep = o.crep();

		void* ptr;
		
		if (crep->has_holder())
			ptr = crep->extractor()(o.ptr());
		else
			ptr = o.ptr();

		return call_fun(L, static_cast<char*>(ptr) + m_pointer_offset);
	}

}} // namespace luabind::detail

#endif // LUABIND_OVERLOAD_REP_IMPL_HPP_INCLUDED
