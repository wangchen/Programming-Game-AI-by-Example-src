extern "C"
{
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

#pragma comment(lib, "lua.lib")
#pragma comment(lib, "lualib.lib")

#include <iostream>
#include <string>
using namespace std;

#include "LuaHelperFunctions.h"
#include "RockPaperScissors.h"




int main()
{
  //create a lua state
  lua_State* pL = lua_open();

  OpenLuaLibraries(pL);

  //register the functions with lua
  lua_register(pL, "cpp_GetAIMove", cpp_GetAIMove);
  lua_register(pL, "cpp_EvaluateTheGuesses", cpp_EvaluateTheGuesses);

  //run the script
  RunLuaScript(pL, "Rock_Paper_Scissors_Using_C++_Funcs.lua");
  
  //tidy up
  lua_close(pL);

  cout << "\n\n\n";
    
  return 0;
}