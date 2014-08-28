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

#ifndef LUABIND_CALL_HPP_INCLUDED
#define LUABIND_CALL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp> 
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/bool.hpp>

#include <luabind/config.hpp>
#include <luabind/detail/policy.hpp>
#include <luabind/yield_policy.hpp>

/*
#define LUABIND_DECL(z, n, text) typedef typename detail::get_policy<n+1,Policies>::type BOOST_PP_CAT(a##n,_policy); \
		typedef typename BOOST_PP_CAT(a##n,_policy)::head BOOST_PP_CAT(a##n,_converter_intermediate); \
		typedef typename BOOST_PP_CAT(a##n,_converter_intermediate)::template generate_converter<A##n, lua_to_cpp>::type BOOST_PP_CAT(p##n,_conv);
#define LUABIND_PARAMS(z,n,text) BOOST_PP_CAT(p##n,_conv)::apply(L, LUABIND_DECORATE_TYPE(A##n), n + 2)
*/

#define LUABIND_DECL(z, n, text) typedef typename find_conversion_policy<n + 1, Policies>::type BOOST_PP_CAT(converter_policy,n); \
		typename BOOST_PP_CAT(converter_policy,n)::template generate_converter<A##n, lua_to_cpp>::type BOOST_PP_CAT(c,n);
//typedef typename BOOST_PP_CAT(converter_policy,n)::template generate_converter<A##n, lua_to_cpp>::type BOOST_PP_CAT(converter,n);
//#define LUABIND_PARAMS(z,n,text) BOOST_PP_CAT(converter,n)::apply(L, LUABIND_DECORATE_TYPE(A##n), n + 2)
#define LUABIND_ADD_INDEX(z,n,text) + BOOST_PP_CAT(converter_policy,n)::has_arg
#define LUABIND_INDEX_MAP(z,n,text) 2 BOOST_PP_REPEAT(n, LUABIND_ADD_INDEX, _)
#define LUABIND_PARAMS(z,n,text) BOOST_PP_CAT(c,n).apply(L, LUABIND_DECORATE_TYPE(A##n), LUABIND_INDEX_MAP(_,n,_))
#define LUABIND_POSTCALL(z,n,text) BOOST_PP_CAT(c,n).converter_postcall(L, LUABIND_DECORATE_TYPE(A##n), LUABIND_INDEX_MAP(_,n,_));

namespace luabind { namespace detail
{
	template<class Policies>
	struct maybe_yield
	{
		static inline int apply(lua_State* L, int nret)
		{
			return ret(L, nret, boost::mpl::bool_<has_yield<Policies>::value>());
		}

		static inline int ret(lua_State* L, int nret, boost::mpl::bool_<true>)
		{
			return lua_yield(L, nret);
		}

		static inline int ret(lua_State*, int nret, boost::mpl::bool_<false>)
		{
			return nret;
		}
	};
	
	template<class T>
	struct returns
	{
		#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/call.hpp>, 1))
		#include BOOST_PP_ITERATE()
	};

	template<>
	struct returns<void>
	{
		#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/call.hpp>, 2))
		#include BOOST_PP_ITERATE()
	};

	#define BOOST_PP_ITERATION_PARAMS_1 (4, (0, LUABIND_MAX_ARITY, <luabind/detail/call.hpp>, 3))
	#include BOOST_PP_ITERATE()
}}

#undef LUABIND_DECL
#undef LUABIND_PARAMS
#undef LUABIND_POSTCALL
#undef LUABIND_ADD_INDEX
#undef LUABIND_INDEX_MAP

#endif // LUABIND_CALL_HPP_INCLUDED

#elif BOOST_PP_ITERATION_FLAGS() == 1

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(T(C::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);

		typedef typename find_conversion_policy<0, Policies>::type converter_policy_ret;
		typename converter_policy_ret::template generate_converter<T, cpp_to_lua>::type converter_ret;

		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)

		converter_ret.apply(L, (obj->*f)
		(
			BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		));

		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

		return maybe_yield<Policies>::apply(L, nret);
//		return nret;
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(T(C::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)) const, C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		typedef typename find_conversion_policy<0, Policies>::type converter_policy_ret;
		typename converter_policy_ret::template generate_converter<T, cpp_to_lua>::type converter_ret;
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		converter_ret.apply(L, (obj->*f)
		(
			BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		));

		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)
		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(T(*f)(C* obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		typedef typename find_conversion_policy<0, Policies>::type converter_policy_ret;
		typename converter_policy_ret::template generate_converter<T, cpp_to_lua>::type converter_ret;
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		converter_ret.apply(L, f
		(
			obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		));
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)
	
		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(T(*f)(const C* obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		typedef typename find_conversion_policy<0, Policies>::type converter_policy_ret;
		typename converter_policy_ret::template generate_converter<T, cpp_to_lua>::type converter_ret;
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		converter_ret.apply(L, f
		(
			*obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		));
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}


	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(T(*f)(C& obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		typedef typename find_conversion_policy<0, Policies>::type converter_policy_ret;
		typename converter_policy_ret::template generate_converter<T, cpp_to_lua>::type converter_ret;
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		converter_ret.apply(L, f
		(
			*obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		));
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(T(*f)(const C& obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		typedef typename find_conversion_policy<0, Policies>::type converter_policy_ret;
		typename converter_policy_ret::template generate_converter<T, cpp_to_lua>::type converter_ret;
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		converter_ret.apply(L, f
		(
			*obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		));
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

#elif BOOST_PP_ITERATION_FLAGS() == 2

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(void(C::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		L = L; // L is used, but metrowerks compiler seem to warn about it before expanding the macros
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		(obj->*f)
		(
			BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		);
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(void(C::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)) const, C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		L = L; // L is used, but metrowerks compiler seem to warn about it before expanding the macros
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		(obj->*f)
		(
			BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		);
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(void(*f)(C* obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		L = L; // L is used, but metrowerks compiler seem to warn about it before expanding the macros
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		f(
			obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		);

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(void(*f)(C& obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		L = L; // L is used, but metrowerks compiler seem to warn about it before expanding the macros
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		f(
			*obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		);

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

	template<class C, class Policies BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	static int call(void(*f)(const C& obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), C* obj, lua_State* L, const Policies*)
	{
		int nargs = lua_gettop(L);
		L = L; // L is used, but metrowerks compiler seem to warn about it before expanding the macros
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_DECL, _)
		f(
			*obj BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM(BOOST_PP_ITERATION(), LUABIND_PARAMS, _)
		);
		BOOST_PP_REPEAT(BOOST_PP_ITERATION(), LUABIND_POSTCALL, _)

		int nret = lua_gettop(L) - nargs;

		const int indices[] =
		{
			1 		/* self */,
			nargs + nret /* result */
			BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), LUABIND_INDEX_MAP, _)
		};

		policy_list_postcall<Policies>::apply(L, indices);

	//	return nret;
		return maybe_yield<Policies>::apply(L, nret);
	}

#elif BOOST_PP_ITERATION_FLAGS() == 3

	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int call(R(*f)(T& BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), T* obj, lua_State* L, const Policies* policies)
	{
		return returns<R>::call(f, obj, L, policies);
	}

	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int call(R(*f)(const T& BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), T* obj, lua_State* L, const Policies* policies)
	{
		return returns<R>::call(f, obj, L, policies);
	}

	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int call(R(*f)(T* BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), T* obj, lua_State* L, const Policies* policies)
	{
		return returns<R>::call(f, obj, L, policies);
	}

	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int call(R(*f)(const T* BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), T* obj, lua_State* L, const Policies* policies)
	{
		return returns<R>::call(f, obj, L, policies);
	}

	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int call(R(T::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), T* obj, lua_State* L, const Policies* policies)
	{
		return returns<R>::call(f, obj, L, policies);
	}

	template<class T, class Policies, class R BOOST_PP_COMMA_IF(BOOST_PP_ITERATION()) BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class A)>
	int call(R(T::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)) const, T* obj, lua_State* L, const Policies* policies)
	{
		return returns<R>::call(f, obj, L, policies);
	}

#endif
