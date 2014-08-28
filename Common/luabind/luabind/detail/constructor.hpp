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

#ifndef LUABIND_CONSTRUCTOR_HPP_INCLUDED
#define LUABIND_CONSTRUCTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/comma_if.hpp>

#include <luabind/config.hpp>
#include <luabind/detail/policy.hpp>
#include <luabind/detail/signature_match.hpp>
#include <luabind/detail/call_member.hpp>

namespace luabind { namespace detail
{
	template<int N>
	struct constructor_helper;

	template<int N>
	struct wrapped_constructor_helper;
	
	#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/constructor.hpp>, 1))
	#include BOOST_PP_ITERATE()

	template<class T, class Policies, class ConstructorSig>
	struct construct_class
	{
		inline static void* apply(lua_State* L)
		{
			typedef constructor_helper<ConstructorSig::arity> ConstrHelp;
			typedef typename ConstrHelp::template apply<T> Caller;
			return Caller::call(L, static_cast<const ConstructorSig*>(0), static_cast<const Policies*>(0));
		}
	};

	template<class T, class Policies, class ConstructorSig>
	struct construct_wrapped_class
	{
		inline static void* apply(lua_State* L, int ref)
		{
			typedef wrapped_constructor_helper<ConstructorSig::arity> ConstrHelp;
			typedef typename ConstrHelp::apply<T> Caller;
			return Caller::call(L, ref, static_cast<const ConstructorSig*>(0), static_cast<const Policies*>(0));
		}
	};

}}

#endif // LUABIND_CONSTRUCTOR_HPP_INCLUDED


#elif BOOST_PP_ITERATION_FLAGS() == 1


#define LUABIND_DECL(z, n, text) typedef typename find_conversion_policy<n+1,Policies>::type BOOST_PP_CAT(converter_policy,n); \
	typedef typename BOOST_PP_CAT(converter_policy,n)::template generate_converter<A##n, lua_to_cpp>::type BOOST_PP_CAT(c_t,n); \
	typename BOOST_PP_CAT(converter_policy,n)::template generate_converter<A##n, lua_to_cpp>::type BOOST_PP_CAT(c,n);
#define LUABIND_PARAM(z,n,text) BOOST_PP_CAT(c,n).BOOST_PP_CAT(c_t,n)::apply(L, LUABIND_DECORATE_TYPE(A##n), n + 2)

	template<>
	struct constructor_helper<BOOST_PP_ITERATION()>
	{
		template<class T>
		struct apply
		{
			template<class Policies, BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, class A)>
			static T* call(lua_State* L, const constructor<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY,A)>*, const Policies*)
			{
				// L is used, but the metrowerks compiler warns about this before expanding the macros
				L = L;
				BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
				return new T(BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAM, _));
			}
		};
	};

	template<>
	struct wrapped_constructor_helper<BOOST_PP_ITERATION()>
	{
		template<class T>
		struct apply
		{
			template<class Policies, BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY, class A)>
			static T* call(lua_State* L, int ref, const constructor<BOOST_PP_ENUM_PARAMS(LUABIND_MAX_ARITY,A)>*, const Policies*)
			{
				BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
					return new T(luabind::object(L, ref, true/*luabind::object::reference()*/) BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAM, _));
			}
		};
	};


#undef LUABIND_PARAM
#undef LUABIND_DECL

#endif // LUABIND_CONSTRUCTOR_HPP_INCLUDED

