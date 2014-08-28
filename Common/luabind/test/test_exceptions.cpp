#include "test.h"

namespace
{
	struct ex: public std::exception
	{
		ex(const char* m): msg(m) {}
		virtual const char* what() const throw() { return msg; }
		const char* msg;
	};

	struct exception_thrower
	{
		exception_thrower() {}
		exception_thrower(int) { throw ex("exception description"); }
		exception_thrower(int, int) { throw "a string exception"; }
		exception_thrower(int, int, int) { throw 10; }
		int f() { throw ex("exception from a member function"); }
		int g() { throw "a string exception"; }
		int h() { throw 10; }
	};

} // anonymous namespace


bool test_exceptions()
{
	try
	{
		using namespace luabind;

		lua_State* L = lua_open();
		lua_closer c(L);
		int top = lua_gettop(L);

		open(L);

		module(L)
		[
			class_<exception_thrower>("exception_thrower")
				.def(constructor<>())
				.def(constructor<int>())
				.def(constructor<int, int>())
				.def(constructor<int, int, int>())
				.def("f", &exception_thrower::f)
				.def("g", &exception_thrower::g)
				.def("h", &exception_thrower::h)
		];

		if (dostring2(L, "a = exception_thrower(1)") != 1) throw 0;
		if (std::string("exception description") != lua_tostring(L, -1)) throw 0;
		lua_pop(L, 1);
		if (dostring2(L, "a = exception_thrower(1,1)") != 1) throw 0;
		if (std::string("a string exception") != lua_tostring(L, -1)) throw 0;
		lua_pop(L, 1);
		if (dostring2(L, "a = exception_thrower(1,1,1)") != 1) throw 0;
		if (std::string("exception_thrower() threw an exception") != lua_tostring(L, -1)) throw 0;
		lua_pop(L, 1);
		if (dostring2(L, "a = exception_thrower()") != 0) throw 0;
		if (dostring2(L, "a:f()") != 1) throw 0;
		if (std::string("exception from a member function") != lua_tostring(L, -1)) throw 0;
		lua_pop(L, 1);
		if (dostring2(L, "a:g()") != 1) throw 0;
		if (std::string("a string exception") != lua_tostring(L, -1)) throw 0;
		lua_pop(L, 1);
		if (dostring2(L, "a:h()") != 1) throw 0;
		if (std::string("exception_thrower:h() threw an exception") != lua_tostring(L, -1)) throw 0;
		lua_pop(L, 1);

		if (top != lua_gettop(L)) return false;
	}
	catch(...)
	{
		return false;
	}

	return true;
}
