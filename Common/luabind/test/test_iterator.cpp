#include "test.h"

extern "C"
{
	#include "lauxlib.h"
	#include "lualib.h"
}

#include <vector>
#include <luabind/iterator_policy.hpp>

namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct IteratorTest
	{
		IteratorTest()
		{
			names.push_back("first one");
			names.push_back("foobar");
			names.push_back("last one");
		}

		std::vector<std::string> names;
	};
	
} // anonymous namespace

bool test_iterator()
{
	using namespace luabind;

	lua_State* L = lua_open();
	lua_baselibopen(L);
	lua_closer c(L);

	open(L);

	module(L)
	[
		class_<IteratorTest>("A")
			.def(constructor<>())
			.def_readonly("names", &IteratorTest::names, return_stl_iterator)
	];

	dostring(L, "a = A()");
	dostring(L, "b = ''");
	dostring(L, "for name in a.names do b = b .. name end");

	if (object_cast<std::string>(get_globals(L)["b"]) != "first onefoobarlast one") return false;

	return true;
}

