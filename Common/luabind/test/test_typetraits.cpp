#include <luabind/detail/typetraits.hpp>
#include <boost/static_assert.hpp>

using namespace luabind::detail;

struct tester {};

void test_type_traits()
{
	BOOST_STATIC_ASSERT(is_nonconst_reference<int&>::value);
	BOOST_STATIC_ASSERT(!is_nonconst_reference<const int&>::value);
	BOOST_STATIC_ASSERT(is_nonconst_reference<tester&>::value);
	BOOST_STATIC_ASSERT(!is_nonconst_reference<const tester&>::value);

	BOOST_STATIC_ASSERT(!is_const_reference<int&>::value);
	BOOST_STATIC_ASSERT(is_const_reference<const int&>::value);
	BOOST_STATIC_ASSERT(!is_const_reference<tester&>::value);
	BOOST_STATIC_ASSERT(is_const_reference<const tester&>::value);

	BOOST_STATIC_ASSERT(!is_const_pointer<int*>::value);
	BOOST_STATIC_ASSERT(is_const_pointer<const int*>::value);
	BOOST_STATIC_ASSERT(!is_const_pointer<tester*>::value);
	BOOST_STATIC_ASSERT(is_const_pointer<const tester*>::value);

	BOOST_STATIC_ASSERT(is_nonconst_pointer<int*>::value);
	BOOST_STATIC_ASSERT(!is_nonconst_pointer<const int*>::value);
	BOOST_STATIC_ASSERT(is_nonconst_pointer<tester*>::value);
	BOOST_STATIC_ASSERT(!is_nonconst_pointer<const tester*>::value);

	BOOST_STATIC_ASSERT(!is_const_reference<const tester>::value);
}
