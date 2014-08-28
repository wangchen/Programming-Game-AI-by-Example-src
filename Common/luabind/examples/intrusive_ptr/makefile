include ../../config

all: intrusive_ptr

intrusive_ptr: intrusive_ptr.cpp
	$(CXX) intrusive_ptr.cpp -o intrusive_ptr $(LUA_PATH) -I- $(BOOST_PATH) -I../../ -L../../lib $(LUA_LIB_PATH) -lluabind -llua -llualib

clean:
	rm -f intrusive_ptr

