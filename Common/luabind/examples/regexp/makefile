include ../../config

all: regexp

regexp: regex_wrap.cpp
	$(CXX) regex_wrap.cpp -o regex_wrap $(LUA_PATH) -I- $(BOOST_PATH) -I../../ -L../../lib $(LUA_LIB_PATH) -lluabind -lboost_regex -llua -llualib

clean:
	rm -f regex_wrap.o

