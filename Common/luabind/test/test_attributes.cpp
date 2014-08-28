#pragma warning( disable: 4097 )
#pragma warning( disable: 4096 )

#include "test.h"

extern "C"
{
	#include "lauxlib.h"
	#include "lualib.h"
}

namespace
{
	LUABIND_ANONYMOUS_FIX int feedback = 0;
	LUABIND_ANONYMOUS_FIX std::string str;

	struct internal 
	{
		std::string name_;
	};

	struct property_test
	{
		property_test(): o(6) 
		{
			m_internal.name_ = "internal name";
		}

		std::string name_;
		int a_;
		float o;
		internal m_internal;

		void set(int a) { a_ = a; feedback = a; }
		int get() const { feedback = a_; return a_; }

		void set_name(const char* name) { name_ = name; str = name; feedback = 0; }
		const char* get_name() const { return name_.c_str(); }

		const internal& get_internal() const { return m_internal; }
	};

	int tester(lua_State* L)
	{
		if (!lua_isnumber(L, 1))
		{
			feedback = 0;
			if (lua_isstring(L, 1))
			{
				str = lua_tostring(L, 1);
			}
		}
		else
		{
			feedback = static_cast<int>(lua_tonumber(L, 1));
		}
		return 0;
	}
} // anonymous namespace

bool test_attributes()
{
	using namespace luabind;

	lua_State* L = lua_open();
	lua_baselibopen(L);
	lua_closer c(L);
	int top = lua_gettop(L);

	luabind::open(L);

	lua_pushstring(L, "tester");
	lua_pushcfunction(L, tester);
	lua_settable(L, LUA_GLOBALSINDEX);

	module(L)
	[
		luabind::class_<internal>("internal")
			.def_readonly("name", &internal::name_),
	
		luabind::class_<property_test>("property")
			.def(luabind::constructor<>())
			.def("get", &property_test::get)
			.def("get_name", &property_test::get_name)
			.property("a", &property_test::get, &property_test::set)
			.property("name", &property_test::get_name, &property_test::set_name)
			.def_readonly("o", &property_test::o)
//#ifndef BOOST_MSVC
			.property("internal", &property_test::get_internal, luabind::dependency(luabind::result, luabind::self))
//#endif
	];

	if (dostring(L, "test = property()")) return false;
	if (dostring(L, "test.a = 5")) return false;
	if (feedback != 5) return false;

	if (dostring(L, "test.name = 'Dew'")) return false;
	if (dostring(L, "tester(test.name)")) return false;
	if (feedback != 0) return false;
	if (str != "Dew") return false;

	if (dostring(L, "function d(x) end d(test.a)")) return false;
	if (feedback != 5) return false;

	if (dostring(L, "test.name = 'mango'")) return false;
	if (feedback != 0) return false;
	if (str != "mango") return false;

	if (dostring(L, "tester(test.o)")) return false;
	if (feedback != 6) return false;

	luabind::object glob = luabind::get_globals(L);

	if (dostring(L, "a = 4")) return false;
	if (glob["a"].type() != LUA_TNUMBER) return false;
	if (dostring(L, "a = test[nil]")) return false;
	if (glob["a"].type() != LUA_TNIL) return false;
	if (dostring(L, "a = test[3.6]")) return false;
	if (glob["a"].type() != LUA_TNIL) return false;

	lua_pushstring(L, "test");
	glob["test_string"].set();

	if (luabind::object_cast<std::string>(glob["test_string"]) != "test") return false;

	luabind::object t = glob["t"];
	lua_pushnumber(L, 4);
	t.set();
	if (luabind::object_cast<int>(t) != 4) return false;
	
	glob["test_string"] = std::string("barfoo");

//	swap overloads doesn't work on vc
#if !defined(BOOST_MSVC) && !defined(BOOST_INTEL_CXX_VERSION)
	std::swap(glob["test_string"], glob["a"]);
	if (object_cast<std::string>(glob["a"]) != "barfoo") return false;
	int type = glob["test_string"].type();
	if (type != LUA_TNIL) return false;

	if (glob["test_string"].type() != LUA_TNIL) return false;
#endif

	if (dostring2(L, "test.o = 5") != 1) return false;
	if (std::string("cannot set attribute 'property.o'") != lua_tostring(L, -1)) return false;
	lua_pop(L, 1);

	if (dostring(L, "tester(test.name)")) return false;
	if (feedback != 0) return false;
	if (str != "mango") return false;

	if (top != lua_gettop(L)) return false;

	dostring(L, "a = property()");
	dostring(L, "b = a.internal");
	dostring(L, "a = nil");
	dostring(L, "collectgarbage(0)");
	dostring(L, "collectgarbage(0)");
	return true;
}
