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



int main()
{
  //create a lua state
  lua_State* pL = lua_open();

  //open the libraries
  OpenLuaLibraries(pL);
  
  RunLuaScript(pL, "cpp_using_lua.lua");
 
  cout << "\n[C++]:  1. Assigning lua string and number types to C++ std::string & int types\n";
  
  //reset the stack index
  lua_settop(pL, 0);

  //put the global variables 'age' and 'name' on the stack.
  lua_getglobal(pL, "age");
  lua_getglobal(pL, "name");

  //check that the variables are the correct type. (notice how the 
  //stack index starts at 1, not 0)
  if (!lua_isnumber(pL, 1) || !lua_isstring(pL, 2))
  {
    cout << "\n[C++]: ERROR: Invalid type!";
  }

  //now assign the values to C++ variables
  string name = lua_tostring(pL, 2);

  //notice the cast to int with this.
  int    age = (int)lua_tonumber(pL, 1);

  cout << "\n\n[C++]: name = " << name 
       << "\n[C++]: age  = " << age << endl;





  cout << "\n\n[C++]:  2. Retrieving simple table";


  //put the table on the stack
  lua_getglobal(pL, "simple_table");

  if (!lua_istable(pL, -1))
  {
    cout << "\n[C++]: ERROR: simple_table is not a valid table";
  }

  else
  {
    //push the key onto the stack
    lua_pushstring(pL, "name");

    //table is now at -2 (key is at -1). lua_gettable now pops the key off
    //the stack and then puts the data found at the key location on the stack
    lua_gettable(pL, -2);

    //check that is the correct type
    if (!lua_isstring(pL, -1))
    {
      cout << "\n[C++]: ERROR: invalid type";
    }

    //grab the data
    name = lua_tostring(pL, -1);

    cout << "\n\n[C++]: name = " << name;

    lua_pop(pL, 1);

    /* now to do the same for the age */

    lua_pushstring(pL, "age");
    lua_gettable(pL, -2);
    if (!lua_isnumber(pL, -1))
    {
      cout << "\n[C++]: ERROR: invalid type";
    }

    //grab the data
    age = (int)lua_tonumber(pL, -1);

    lua_pop(pL, 1);

    cout << "\n[C++]: age  = " << age;
    
  }

 

   cout << "\n\n[C++]: 3. Calling a simple Lua function: add(a,b)";

   //get the function from the global table and push it on the stack
   lua_getglobal(pL, "add");

   //check that it is there
   if (!lua_isfunction(pL, -1))
   {
     cout << "\n\n[C++]: Oops! The lua function 'add' has not been defined";
   }

   //push some variables onto the lua stack
   lua_pushnumber(pL, 5);
   lua_pushnumber(pL, 8);

   //calling the function with parameters to set the number of parameters in
   //the lua func and how many return values it returns. Puts the result at
   //the top of the stack.
   lua_call(pL, 2, 1);

   //grab the result from the top of the stack
   int result = lua_tonumber(pL, -1);

   lua_pop(pL, 1);

   cout << "\n\n[C++]: <lua>add(5,8) = " << result;



  
  //tidy up
  lua_close(pL);

  cout << "\n\n\n";
    
  return 0;
}