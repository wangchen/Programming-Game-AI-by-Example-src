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

#ifndef LUABIND_SIGNATURE_MATCH_HPP_INCLUDED
#define LUABIND_SIGNATURE_MATCH_HPP_INCLUDED

#include <luabind/config.hpp>

#include <boost/config.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp> 
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits.hpp>

#include <luabind/detail/primitives.hpp>
#include <luabind/detail/object_rep.hpp>
#include <luabind/detail/class_rep.hpp>
#include <luabind/detail/policy.hpp>

namespace luabind
{

	namespace detail
	{
		template<class A>
		struct constructor_arity_helper
		{
			BOOST_STATIC_CONSTANT(int, value = 1);
		};

		template<>
		struct constructor_arity_helper<luabind::detail::null_type>
		{
			BOOST_STATIC_CONSTANT(int, value = 0);
		};
	}


#define LUABIND_SUM(z, n, _) detail::constructor_arity_helper<A##n >::value + 

	template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(LUABIND_MAX_ARITY, class A, detail::null_type)>
	struct constructor
	{
		BOOST_STATIC_CONSTANT(int, arity = BOOST_PP_REPEAT(LUABIND_MAX_ARITY, LUABIND_SUM, _) 0);
	};

#undef LUABIND_SUM
}

namespace luabind { namespace detail
{
	template<class A, int Index, class Policies>
	struct match_single_param_base
	{
		static inline bool apply(lua_State*L, int& m, int start_index)
		{
			typedef typename find_conversion_policy<Index + 1, Policies>::type converter_policy;
			typedef typename converter_policy::template generate_converter<A, lua_to_cpp>::type converter;
			int r = converter::match(L, LUABIND_DECORATE_TYPE(A), Index + start_index);
			if (r < 0) return true;
			m += r;
			return false;
		}
	};

	template<class A, int Index, class Policies>
	struct match_single_param_base_nada
	{
		static inline bool apply(lua_State*L, int& m, int start_index)
		{
			return false;
		}
	};

	template<class A, int Index, class Policies>
	struct match_single_param
		: boost::mpl::if_<boost::is_same<A, luabind::detail::null_type>
			, match_single_param_base_nada<A,Index,Policies>
			, match_single_param_base<A,Index,Policies>
			>::type
	{
	};

#define LUABIND_MATCH_DECL(z,n,_) typedef typename find_conversion_policy<n + 1, Policies>::type BOOST_PP_CAT(converter_policy,n); \
	typedef typename BOOST_PP_CAT(converter_policy,n)::template generate_converter<BOOST_PP_CAT(A,n), lua_to_cpp>::type BOOST_PP_CAT(converter,n); \
	int BOOST_PP_CAT(r,n) = BOOST_PP_CAT(converter,n)::match(L, LUABIND_DECORATE_TYPE(BOOST_PP_CAT(A,n)), start_index + n);\
	if (BOOST_PP_CAT(r,n) < 0) return -1; \
	else m += BOOST_PP_CAT(r,n);

#define LUABIND_MATCH_PARAM(z, n, _) if (match_single_param<A##n, n, Policies>::apply(L, m, start_index)) return -1;

	template<int N> struct match_constructor;

	#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/signature_match.hpp>, 2))
	#include BOOST_PP_ITERATE()

#undef LUABIND_MATCH_DECL

	// this is a function that checks if the lua stack (starting at the given start_index) matches
	// the types in the constructor type given as 3:rd parameter. It uses the Policies given as
	// 4:th parameter to do the matching. It returns the total number of cast-steps that needs to
	// be taken in order to match the parameters on the lua stack to the given parameter-list. Or,
	// if the parameter doesn't match, it returns -1.
	template<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, class A), class Policies>
	int match_params(lua_State*L, int start_index, const constructor<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, A)>* c, const Policies* p)
	{

		typedef constructor<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, A)> sig_t;
//		int m = 0;
//		BOOST_PP_REPEAT(LUABIND_MAX_ARITY, LUABIND_MATCH_PARAM, _);
//		return m;
		return match_constructor<sig_t::arity>::apply(L, start_index, c, p);
	}

#undef LUABIND_MATCH_PARAMS


	template<class Sig, int StartIndex, class Policies>
	struct constructor_match
	{
		inline static int apply(lua_State* L)	
		{
			int top = lua_gettop(L) - StartIndex + 1;
			if (top != Sig::arity) return -1;

			return match_params(L, StartIndex, reinterpret_cast<Sig*>(0), reinterpret_cast<Policies*>(0));
		}};

	#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/signature_match.hpp>, 1))
	#include BOOST_PP_ITERATE()

}}

#endif // LUABIND_SIGNATURE_MATCH_HPP_INCLUDED

#elif BOOST_PP_ITERATION_FLAGS() == 1

// non-member functions

	// non-const non-member function this as a pointer
	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int match(R(*)(T* BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), lua_State* L, bool const_object, const Policies* policies)
	{
		if (const_object/* || lua_gettop(L) != BOOST_PP_ITERATION() + 1*/) return -1;
		typedef constructor<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> ParameterTypes;
		return match_params(L, 2, static_cast<ParameterTypes*>(0), policies);
	}

	// const non-member function this as a pointer
	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int match(R(*)(const T* BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), lua_State* L, bool const_object, const Policies* policies)
	{
		//if (lua_gettop(L) != BOOST_PP_ITERATION() + 1) return -1;
		typedef constructor<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> ParameterTypes;
		int m = match_params(L, 2, static_cast<ParameterTypes*>(0), policies);
		return const_object ? m : m + 1;
	}

	// non-const non-member function this as a reference
	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int match(R(*)(T& BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), lua_State* L, bool const_object, const Policies* policies)
	{
		if (const_object/* || lua_gettop(L) != BOOST_PP_ITERATION() + 1*/) return -1;
		typedef constructor<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> ParameterTypes;
		return match_params(L, 2, static_cast<ParameterTypes*>(0), policies);
	}

	// const non-member function this as a reference
	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int match(R(*)(const T& BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), lua_State* L, bool const_object, const Policies* policies)
	{
		//if (lua_gettop(L) != BOOST_PP_ITERATION() + 1) return -1;
		typedef constructor<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> ParameterTypes;
		int m = match_params(L, 2, static_cast<ParameterTypes*>(0), policies);
		return const_object ? m : m + 1;
	}

	// member functions

	// non-const member function
	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int match(R(T::*)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), lua_State* L, bool const_object, const Policies* policies)
	{
		if (const_object/* || lua_gettop(L) != BOOST_PP_ITERATION() + 1*/) return -1;
		typedef constructor<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> ParameterTypes;
		return match_params(L, 2, static_cast<ParameterTypes*>(0), policies);
	}

	// const member function
	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int match(R(T::*)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)) const, lua_State* L, bool const_object, const Policies* policies)
	{
		//if (lua_gettop(L) != BOOST_PP_ITERATION() + 1) return -1;
		typedef constructor<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> ParameterTypes;
		int m = match_params(L, 2, static_cast<ParameterTypes*>(0), policies);
		return const_object ? m : m + 1;
	}
	
#elif BOOST_PP_ITERATION_FLAGS() == 2

	template<>
	struct match_constructor<BOOST_PP_ITERATION()>
	{
		template<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, class A), class Policies>
		static int apply(lua_State* L, int start_index, const constructor<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, A)>*, const Policies*)
		{
			int m = 0;
			BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_MATCH_DECL, _)
			return m;
		}
	};

#endif

