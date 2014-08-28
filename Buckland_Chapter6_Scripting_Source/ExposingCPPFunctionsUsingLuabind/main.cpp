//include the libraries
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "lualib.lib")

//turn off the inevitable warnings
#pragma warning (disable : 4786)

extern "C"
{
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

#include <iostream>
using namespace std;

//include the luabind headers. Make sure you have the paths set correctly
//to the lua, luabind and Boost files.
#include <luabind/luabind.hpp>
using namespace luabind;

//include the helper functions
#include "LuaHelperFunctions.h"


//define a couple of simple functions
void HelloWorld()
{
  cout << "\n[C++]: Hello World!" << endl;
}

int add(int a, int b)
{
  return a + b;
}



int main()
{
  //create a lua state
  lua_State* pLua = lua_open();

  //open the lua std libraries
  OpenLuaLibraries(pLua);

  //open luabind
  open(pLua);

  module(pLua)
  [
	  def("HelloWorld", &HelloWorld),
    def("add", &add)
  ];
 
  //load and run the script
  RunLuaScript(pLua, "ExposingCPPFunctionsToLua.lua");

  
  //tidy up
  lua_close(pLua);

    
  return 0;
}