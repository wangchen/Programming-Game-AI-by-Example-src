//include the libraries
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "lualib.lib")
#pragma warning(disable : 4786)

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

#include <iostream>
#include <string>
using namespace std;

//include the luabind headers. Make sure you have the paths set correctly
//to the lua, luabind and Boost files.
#include <luabind/luabind.hpp>
using namespace luabind;

#include "LuaHelperFunctions.h"

int main()
{
  //create a lua state
  lua_State * pLua = lua_open();

  //open the libraries
  OpenLuaLibraries(pLua);

  //open luabind
  open(pLua);

  //load and run the script
  RunLuaScript(pLua, "classes_in_lua.lua");

  lua_close(pLua);

  return 0;
}
