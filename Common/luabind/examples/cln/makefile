include ../../config

all: cln_test

cln_test: cln_test.cpp
	$(CXX) cln_test.cpp -o cln_test $(LUA_PATH) -I- $(BOOST_PATH) -I../../ $(LUA_LIB_PATH) -L../../lib -lluabind -llua -llualib -lcln

clean:
	rm -f cln_test.o

