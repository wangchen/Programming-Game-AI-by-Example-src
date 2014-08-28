#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <memory>

#include "test.h"

namespace luabind
{
	template<class T>
	T* get_pointer(boost::shared_ptr<T>& p) { return p.get(); }

	template<class A>
	boost::shared_ptr<const A>* get_const_holder(boost::shared_ptr<A>*)
	{
		return 0;
	}
}

namespace
{

	LUABIND_ANONYMOUS_FIX int feedback = 0;

	struct base
	{
		base(): n(4) { feedback = 3; }
		virtual ~base() { feedback = 1; }

		void f(int)
		{
			feedback = n;
		}

		int n;
	};

	// this is here to make sure the pointer offsetting works
	struct first_base
	{
		virtual void a() {}
		int padding;
	};

	struct derived: first_base, base
	{
		derived(): n2(7) { feedback = 7; }
		void f() { feedback = 5; }
		int n2;
	};

	void tester(base* t)
	{
		if (t->n == 4) feedback = 2;
	}

	void tester_(derived* t)
	{
		if (t->n2 == 7) feedback = 8;
	}

	void tester2(boost::shared_ptr<base> t)
	{
		if (t->n == 4) feedback = 9;
	}

	void tester3(boost::shared_ptr<const base> t)
	{
		if (t->n == 4) feedback = 10;
	}

	void tester4(const boost::shared_ptr<const base>& t)
	{
		if (t->n == 4) feedback = 11;
	}

	void tester5(const boost::shared_ptr<const base>* t)
	{
		if ((*t)->n == 4) feedback = 12;
	}

	void tester6(const boost::shared_ptr<base>* t)
	{
		if ((*t)->n == 4) feedback = 13;
	}

	void tester7(boost::shared_ptr<base>* t)
	{
		if ((*t)->n == 4) feedback = 14;
	}

	boost::shared_ptr<base> tester9()
	{
		feedback = 20;
		return boost::shared_ptr<base>(new base());
	}

	struct tester10
	{
		tester10() : m_member(new base()) {}
		const boost::shared_ptr<base>& test() { return m_member; }
		boost::shared_ptr<base> m_member;
	};

	struct base_2 {};
	
	LUABIND_ANONYMOUS_FIX int pointer_cnt = 0;

	struct base_holder
	{
		static int counter;
			  
		explicit base_holder(base_2* p): ptr(p), secret(2068) 
		{ ++counter; }

		base_holder(const base_holder&)
			: secret(9999)
		{
			++counter;
		}

		~base_holder()
		{ 
			--counter;
			assert(secret == 2068);
			secret = 0;
		}

		base_2* get() const { return ptr; }

		base_2* ptr;

		int secret;
	};

	int base_holder::counter = 0;
	
	struct const_base_holder
	{
		static int counter;
			  
		explicit const_base_holder(const base_2* p): ptr(p), secret(9999) 
		{
			++counter;
		}

		const_base_holder(const base_holder& x)
			: secret(9999)
		{ ++counter; }

		const_base_holder(const const_base_holder&)
			: secret(9999)
		{
			++counter;
		}

		~const_base_holder()
		{ 
			--counter;
			assert(secret == 9999);
			secret = 0;
		}

		const base_2* get() const { return ptr; }

		const base_2* ptr;

		int secret;
		char garbage[16];
	};

	int const_base_holder::counter = 0;

	void tester8(const const_base_holder&)
	{
		feedback = 100;
	}

	void tester15(const_base_holder)
	{
		feedback = 101;
	}
	
	const_base_holder tester16()
	{
		return const_base_holder(0);
	}
	
} // anonymous namespace

namespace luabind
{
	base_2* get_pointer(const base_holder& p) { return p.get(); }
	const base_2* get_pointer(const const_base_holder& p) { return p.get(); }

	const_base_holder* get_const_holder(base_holder*)
	{
		return 0;
	}
}

bool test_held_type()
{
	using namespace luabind;

	boost::shared_ptr<base> ptr(new base());

	{
		lua_State* L = lua_open();
		lua_baselibopen(L);
		lua_closer c(L);
		int top = lua_gettop(L);

		open(L);

		module(L)
		[
			def("tester", &tester),
			def("tester", &tester_),
			def("tester2", &tester2),
			def("tester3", &tester3),
			def("tester4", &tester4),
			def("tester5", &tester5),
			def("tester6", &tester6),
			def("tester7", &tester7),
			def("tester8", &tester8),
			def("tester9", &tester9),
			def("tester15", &tester15),
			def("tester16", &tester16),
	
			class_<base, boost::shared_ptr<base> >("base")
				.def(constructor<>())
				.def("f", &base::f),

			class_<derived, base, boost::shared_ptr<base> >("derived")
				.def(constructor<>())
				.def("f", &derived::f),

			class_<tester10>("tester10")
				.def(constructor<>())
				.def("test", &tester10::test),

			class_<base_2, base_holder>("base_")
				.def(constructor<>())
		];

		lua_gettop(L);

		object g = get_globals(L);
		g["test"] = ptr;
		g["foobar"] = boost::shared_ptr<const base>(new base());

		if (dostring(L, "tester(test)")) return false;
		if (feedback != 2) return false;
		if (dostring(L, "a = base()")) return false;
		if (feedback != 3) return false;
		if (dostring(L, "b = derived()")) return false;
		if (feedback != 7) return false;
		if (dostring(L, "tester(a)")) return false;
		if (feedback != 2) return false;
		if (dostring(L, "tester(b)")) return false;
		if (feedback != 8) return false;
		if (dostring(L, "tester2(b)")) return false;
		if (feedback != 9) return false;
		if (dostring(L, "tester3(b)")) return false;
		if (feedback != 10) return false;
		if (dostring(L, "tester4(foobar)")) return false;
		if (feedback != 11) return false;
		if (dostring(L, "tester5(foobar)")) return false;
		if (feedback != 12) return false;
		if (dostring(L, "tester6(b)")) return false;
		if (feedback != 13) return false;
		if (dostring(L, "tester7(b)")) return false;
		if (feedback != 14) return false;
//		if (dostring(L, "tester8(b)")) return false;
//		if (feedback != 19) return false;
		if (dostring(L, "c = tester9()")) return false;
		if (feedback != 3) return false;
		feedback= 0;

		if (dostring(L, "d = tester10()")) return false;
		if (dostring(L, "e = d:test()")) return false;
		if (feedback != 3) return false;

		if (dostring(L, "a = base_()")) return false;
		if (dostring(L, "tester8(a)")) return false;
		if (feedback != 100) return false;
		if (dostring(L, "tester15(a)")) return false;
		if (feedback != 101) return false;
		if (dostring(L, "tester8(tester16())")) return false;
		if (feedback != 100) return false;
		
		if (top != lua_gettop(L)) return false;
	}

	ptr.reset();
	
	if (feedback != 1) return false;

	if (base_holder::counter != 0) return false;
	if (const_base_holder::counter != 0) return false;

	return true;
}
