include ../config

SOURCES = \
	main.cpp \
	test_iterator.cpp \
	test_lua_classes.cpp \
	test_typetraits.cpp \
	test_construction.cpp \
	test_operators.cpp \
	test_attributes.cpp \
	test_exceptions.cpp \
	test_const.cpp \
	test_null_pointer.cpp \
	test_implicit_cast.cpp \
	test_policies.cpp \
	test_free_functions.cpp \
	test_object.cpp \
	test_held_type.cpp \
	test_scope.cpp \
	test_yield.cpp

TARGET = test_luabind




OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -O3 $(OBJECTS) $(LUA_LIB_PATH) -L../lib -lluabind -llua -llualib -o $@

%.o:%.cpp
	$(CXX) -Wall -ftemplate-depth-50 -O3 $(CONFIG) $(LUA_PATH) -I. -I- -I../ $(BOOST_PATH) -c $? -o $@

relink:
	rm -f $(TARGET)
	make

clean:
	rm -f $(OBJECTS) $(TARGET) core

