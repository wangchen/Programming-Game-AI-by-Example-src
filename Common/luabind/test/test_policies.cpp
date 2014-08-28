#include "test.h"

#include <luabind/out_value_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/copy_policy.hpp>

namespace
{

	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct policies_test_class
	{
		std::string name_;

		policies_test_class() { feedback++; }
		policies_test_class(const char* name): name_(name) { feedback++; }
		~policies_test_class() { feedback--; }

		policies_test_class* make(const char* name) const
		{
			return new policies_test_class(name);
		}

		void f(policies_test_class* p) { delete p; }

		const policies_test_class* internal_ref() { return this; }

		policies_test_class* self_ref()
		{
			return this;
		}

//	private:
		policies_test_class(const policies_test_class&) {}
	};

	policies_test_class global;

	void out_val(float* f) { *f = 3.f; }
	policies_test_class* copy_val() { return &global; }

	struct secret_type {};

	secret_type sec_;
	
	secret_type* secret() { return &sec_; }

} // anonymous namespace

bool test_policies()
{
	try
	{
		using namespace luabind;

		lua_State* L = lua_open();
		lua_closer c(L);
		lua_baselibopen(L);

		int top = lua_gettop(L);

		luabind::open(L);

		module(L)
		[
			class_<policies_test_class>("test")
				.def(constructor<>())
				.def("f", &policies_test_class::f, adopt(_1))
				.def("make", &policies_test_class::make, adopt(return_value))
				.def("internal_ref", &policies_test_class::internal_ref, dependency(return_value, self))
				.def("self_ref", &policies_test_class::self_ref, return_reference_to(self)),

			def("out_val", &out_val, pure_out_value(_1)),
			def("copy_val", &copy_val, copy(result)),
			def("secret", &secret, discard_result)
		];

		feedback = 1;

		if (dostring(L, "a = secret()")) return false;
		
		// copy
		if (dostring(L, "a = copy_val()")) return false;
		if (dostring(L, "a = nil")) return false;
		if (dostring(L, "collectgarbage(0)")) return false;
		if (feedback != 0) return false;

		// out_value
		if (dostring(L, "a = out_val()")) return false;

		// return_reference_to
		if (dostring(L, "a = test()")) return false;
		if (feedback != 1) return false;
		if (dostring(L, "b = a:self_ref()")) return false;
		if (dostring(L, "a = nil")) return false;
		if (dostring(L, "collectgarbage(0)")) return false;
		if (feedback != 1) return false;
		if (dostring(L, "b = nil")) return false;
		if (dostring(L, "collectgarbage(0)")) return false;
		if (feedback != 0) return false;
	
		// dependency
		if (dostring(L, "a = test()")) return false;
		if (feedback != 1) return false;
		if (dostring(L, "b = a:internal_ref()")) return false;
		if (dostring(L, "a = nil")) return false;
		if (dostring(L, "collectgarbage(0)")) return false;
		if (feedback != 1) return false;
		if (dostring(L, "b = nil")) return false;
		if (dostring(L, "collectgarbage(0)")) return false; // two gc-cycles because dependency-table won't be collected in the same cycle
		if (dostring(L, "collectgarbage(0)")) return false; // as the object_rep
		if (feedback != 0) return false;

		// adopt
		if (dostring(L, "a = test()")) return false;
		if (feedback != 1) return false;
		if (dostring(L, "b = a:make('tjosan')")) return false;
		if (feedback != 2) return false;
		if (dostring(L, "a:f(b)")) return false;

		if (top != lua_gettop(L)) return false;

		c.release();
		if (feedback != 0) return false;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

