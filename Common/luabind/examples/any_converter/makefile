include ../../config

all: any_converter

any_converter: any_converter.cpp
	$(CXX) any_converter.cpp -O3 -o any_converter $(LUA_PATH) -I- $(BOOST_PATH) -I../../ -L../../lib $(LUA_LIB_PATH) -lluabind -llua -llualib

clean:
	rm -f any_converter.o

