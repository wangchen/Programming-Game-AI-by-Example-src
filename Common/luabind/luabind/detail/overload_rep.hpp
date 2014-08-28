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


#if !BOOST_PP_IS_ITERATING

#ifndef LUABIND_OVERLOAD_REP_HPP_INCLUDED
#define LUABIND_OVERLOAD_REP_HPP_INCLUDED

#include <luabind/config.hpp>

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repeat.hpp>

#include <luabind/detail/overload_rep_base.hpp>

#include <luabind/detail/class_rep.hpp>

namespace luabind { namespace detail
{
	struct dummy_ {};

	// this class represents a specific overload of a member-function.
	struct overload_rep: public overload_rep_base
	{
		#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/overload_rep.hpp>, 1))
		#include BOOST_PP_ITERATE()

		bool operator==(const overload_rep& o)
		{
			if (o.m_const != m_const) return false;
			if (o.m_arity != m_arity) return false;
			if (o.m_num_args != m_num_args) return false;
			for (int i = 0; i < m_num_args; ++i)
				if (!(LUABIND_TYPE_INFO_EQUAL(m_params[i], o.m_params[i]))) return false;
			return true;
		}

//		inline int match(lua_State* L, int num_params) const { if (num_params != m_arity) return -1; return m_match_fun(L); }

		void add_offset(int offset) throw() { m_pointer_offset += offset; }
		int offset() const throw() { return m_pointer_offset; }

		inline void set_fun(boost::function2<int,lua_State*,void*>& f) { call_fun = f; }
		inline int call(lua_State* L, const object_rep& o) const;

		boost::function2<int,lua_State*,void*> call_fun;

	private:

		// the offset we need to apply to the object pointer when calling this method.
		// it depends on which class_rep this method is found in
		int m_pointer_offset;

		// the number of parameters this overload takes
		// these are used to detect when a method is overridden by a derived class.
//		int m_arity;
		int m_num_args;
		// the types of the parameter it takes
		LUABIND_TYPE_INFO m_params[LUABIND_MAX_ARITY];
		// is true if the overload is const (this is a part of the signature)
		bool m_const;
	};

}} // namespace luabind::detail

#endif // LUABIND_OVERLOAD_REP_HPP_INCLUDED

#elif BOOST_PP_ITERATION_FLAGS() == 1

#define LUABIND_PARAM(z, n, _) m_params[n] =LUABIND_TYPEID(A##n);
#define LUABIND_POLICY_DECL(z,n,text) typedef typename find_conversion_policy<n + 1, Policies>::type BOOST_PP_CAT(p,n);
#define LUABIND_ARITY(z,n,text) + BOOST_PP_CAT(p,n)::has_arg

		// overloaded template funtion that initializes the parameter list
		// called m_params and the m_arity member.
		template<class R, class T BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A), class Policies>
		overload_rep(R(T::*)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), Policies*)
			: m_pointer_offset(0)
			, m_num_args(BOOST_PP_ITERATION())
			, m_const(false)
		{
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_PARAM, _)
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POLICY_DECL, _)
			m_arity = 0 BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_ARITY, 0);
		}

		template<class R, class T BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A), class Policies>
		overload_rep(R(T::*)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)) const, Policies*)
			: m_pointer_offset(0)
			, m_num_args(BOOST_PP_ITERATION())
			, m_const(true)
		{
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_PARAM, _)
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POLICY_DECL, _)
			m_arity = 0 BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_ARITY, 0);
		}

		// non-member functions

		template<class R, class T BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A), class Policies>
		overload_rep(R(*)(T* BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), Policies*)
			: m_pointer_offset(0)
			, m_num_args(BOOST_PP_ITERATION())
			, m_const(false)
		{
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_PARAM, _)
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POLICY_DECL, _)
			m_arity = 0 BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_ARITY, 0);
		}

		template<class R, class T BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A), class Policies>
		overload_rep(R(*)(const T* BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), Policies*)
			: m_pointer_offset(0)
			, m_num_args(BOOST_PP_ITERATION())
			, m_const(true)
		{
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_PARAM, _)
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POLICY_DECL, _)
			m_arity = 0 BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_ARITY, 0);
		}

		template<class R, class T BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A), class Policies>
		overload_rep(R(*)(T& BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), Policies*)
			: m_pointer_offset(0)
			, m_num_args(BOOST_PP_ITERATION())
			, m_const(false)
		{
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_PARAM, _);
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POLICY_DECL, _)
			m_arity = 0 BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_ARITY, 0);
		}

		template<class R, class T BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A), class Policies>
		overload_rep(R(*)(const T& BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), Policies*)
			: m_pointer_offset(0)
			, m_num_args(BOOST_PP_ITERATION())
			, m_const(true)
		{
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_PARAM, _)
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POLICY_DECL, _)
			m_arity = 0 BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_ARITY, 0);
		}

#undef LUABIND_PARAM

#endif
