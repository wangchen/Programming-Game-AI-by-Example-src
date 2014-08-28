//include the libraries
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "lualib.lib")
#pragma warning (disable : 4786)

extern "C"
{
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

#include <string>
#include <iostream>
using namespace std;

//include the luabind headers. Make sure you have the paths set correctly
//to the lua, luabind and Boost files.
#include <luabind/luabind.hpp>
using namespace luabind;

#include "LuaHelperFunctions.h"
#include "Animal.h"
#include "Pet.h"




void RegisterAnimalWithLua(lua_State* pLua)
{
  module(pLua)
  [
    class_<Animal>("Animal")
    .def(constructor<string, int>())
    .def("Speak", &Animal::Speak)
    .def("NumLegs", &Animal::NumLegs)   
  ];  
}

void RegisterPetWithLua(lua_State* pLua)
{
  module(pLua)
    [
      class_<Pet, bases<Animal> >("Pet")
      .def(constructor<string, string, int>())
      .def("GetName", &Pet::GetName)  
    
    ];  
}


int main()
{
  //create a lua state
  lua_State* pLua = lua_open();

  //open the libraries
  OpenLuaLibraries(pLua);

  //open luabind
  open(pLua);

  RegisterAnimalWithLua(pLua);
  RegisterPetWithLua(pLua);
 
  //load and run the script
  RunLuaScript(pLua, "ExposingCPPClassesToLua.lua");

  lua_close(pLua);



  
    
  return 0;
}