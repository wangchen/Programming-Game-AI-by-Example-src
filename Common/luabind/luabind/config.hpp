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


#ifndef LUABIND_CONFIG_HPP_INCLUDED
#define LUABIND_CONFIG_HPP_INCLUDED

#include <boost/config.hpp>

#ifdef BOOST_MSVC
	#define LUABIND_ANONYMOUS_FIX static
#else
	#define LUABIND_ANONYMOUS_FIX
#endif

#if defined (BOOST_MSVC) && (BOOST_MSVC <= 1200)

#define LUABIND_MSVC_TYPENAME

#define for if (false) {} else for

#include <cstring>

namespace std
{
	using ::strlen;
	using ::strcmp;
	using ::type_info;
}

#else

#define LUABIND_MSVC_TYPENAME typename

#endif

// the maximum number of arguments of functions that's
// registered. Must at least be 2
#ifndef LUABIND_MAX_ARITY
	#define LUABIND_MAX_ARITY 5
#elif LUABIND_MAX_ARITY <= 1
	#undef LUABIND_MAX_ARITY
	#define LUABIND_MAX_ARITY 2
#endif

// the maximum number of classes one class
// can derive from
// max bases must at least be 1
#ifndef LUABIND_MAX_BASES
	#define LUABIND_MAX_BASES 4
#elif LUABIND_MAX_BASES <= 0
	#undef LUABIND_MAX_BASES
	#define LUABIND_MAX_BASES 1
#endif

// LUABIND_NO_ERROR_CHECKING
// define this to remove all error checks
// this will improve performance and memory
// footprint.
// if it is defined matchers will only be called on
// overloaded functions, functions that's
// not overloaded will be called directly. The
// parameters on the lua stack are assumed
// to match those of the function.
// exceptions will still be catched when there's
// no error checking.

// LUABIND_DONT_COPY_STRINGS
// define this if you only pass static constant strings to
// the def() methods. It will make luabind expect the
// strings to exist as long as the program is running.
// Luabind will not copy the strings in this case.

// LUABIND_NOT_THREADSAFE
// this define will make luabind non-thread safe. That is,
// it will rely on a static variable. You can still have
// multiple lua states and use coroutines, but only
// one of your real threads may run lua code.

// If you don't want to use the rtti supplied by C++
// you can supply your own type-info structure with the
// LUABIND_TYPE_INFO define. Your type-info structure
// must be copyable and it must be able to compare itself
// against other type-info structures. You supply the compare
// function through the LUABIND_TYPE_INFO_EQUAL()
// define. It should compare the two type-info structures
// it is given and return true if they represent the same type
// and false otherwise. You also have to supply a function
// to generate your type-info structure. You do this through
// the LUABIND_TYPEID() define. It takes a type as it's
// parameter. That is, a compile time parameter. To use it
// you probably have to make a traits class with specializations
// for all classes that you have type-info for.

#ifndef LUABIND_TYPE_INFO
	#define LUABIND_TYPE_INFO const std::type_info*
	#define LUABIND_TYPEID(t) &typeid(t)
	#define LUABIND_TYPE_INFO_EQUAL(i1, i2) *i1 == *i2
	#define LUABIND_INVALID_TYPE_INFO &typeid(detail::null_type)
#endif

// LUABIND_NO_EXCEPTIONS
// this define will disable all usage of try, catch and throw in
// luabind. This will in many cases disable runtime-errors, such
// as invalid casts, when calling lua-functions that fails or
// returns values that cannot be converted by the given policy.
// Luabind requires that no function called directly or indirectly
// by luabind throws an exception (throwing exceptions through
// C code has undefined behavior, lua is written in C).

#endif // LUABIND_CONFIG_HPP_INCLUDED

