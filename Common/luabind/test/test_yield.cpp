#include "test.h"
#include <luabind/yield_policy.hpp>
#include <stdio.h>

namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct test_class
	{
		test_class(): n(0) {}

		int f() const
		{
			return const_cast<int&>(n)++;
		}

		int n;
	};

	int f(int a)
	{
		return 9;
	}

	int j(lua_State* L)
	{
		lua_pushnumber(L, 9);
		return lua_yield(L, 1);
	}

	void f() {}
}

#include <iostream>

bool test_yield()
{
	using namespace luabind;
	{
		lua_State* L = lua_open();
		lua_baselibopen(L);
		lua_closer c(L);

		open(L);

		module(L)
		[
			class_<test_class>("test")
				.def(constructor<>())
				.def("f", &test_class::f, yield)
		];
/*
		dostring(L, "function g() a = test() for i = 1, 10 do print(a:f()) end end");

		lua_pushstring(L, "j");
		lua_pushcclosure(L, j, 0);
		lua_settable(L, LUA_GLOBALSINDEX);

		lua_State* thread = lua_newthread(L);
		lua_pushstring(thread, "g");
		lua_gettable(thread, LUA_GLOBALSINDEX);

		if (lua_resume(thread, 0))
		{
			std::cout << "error: " << lua_tostring(thread, -1) << '\n';
		}

		for (int i = 0; i < 10; ++i)
		{
			std::cout << "iteration: " << i << ", top: " << lua_gettop(thread) << '\n';

			lua_resume(thread, lua_gettop(thread));
		}*/
	}

	return true;
}

