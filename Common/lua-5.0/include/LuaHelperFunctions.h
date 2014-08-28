#ifndef LUA_HELPER_FUNCS
#define LUA_HELPER_FUNCS

//get rid of the annoying but unavoidable forcing int to bool warning
#pragma warning (disable:4800)

extern "C"
{
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}


#include <string>
#include "misc/utils.h"
#include "misc/Stream_Utility_Functions.h"





struct LuaExceptionGuard
{
  lua_State*  pLua;
  
  LuaExceptionGuard(lua_State* L):pLua(L){}
  
  ~LuaExceptionGuard()
  {
    lua_close(pLua);
  }
};



//makes all the lua libraries available
inline void OpenLuaLibraries(lua_State* pLua)
{
  //open the libraries
  luaopen_base(pLua);
  luaopen_string(pLua);
  luaopen_table(pLua);
  luaopen_math(pLua);
  luaopen_io(pLua);
}

//------------------------------- RunScript -----------------------------------
//
//  runs a script file
//-----------------------------------------------------------------------------
inline void RunLuaScript(lua_State* L, const char* script_name)
{
  if (int error = lua_dofile(L, script_name) != 0)
  {
    throw std::runtime_error("ERROR(" + ttos(error) + "): Problem with lua script file " + script_name);
  }
}

//----------------------------- PopLuaNumber-----------------------------------
//
//  a function template to retrieve a number from the lua stack
//-----------------------------------------------------------------------------
template <class T>
inline T PopLuaNumber(lua_State* pL, const char* name)
{
  lua_settop(pL, 0);

  lua_getglobal(pL, name);

  //check that the variable is the correct type. If it is not throw an
  //exception
  if (!lua_isnumber(pL, 1))
  {
    std::string err("<PopLuaNumber> Cannot retrieve: ");

    throw std::runtime_error(err + name);
  }

  //grab the value, cast to the correct type and return
  T val = (T)lua_tonumber(pL, 1);

  //remove the value from the stack
  lua_pop(pL, 1);

  return val;
}


//--------------------------- PopLuaString ------------------------------------
//-----------------------------------------------------------------------------
inline std::string PopLuaString(lua_State* pL, const char* name)
{
  lua_settop(pL, 0);

  lua_getglobal(pL, name);

  //check that the variable is the correct type. If it is not throw an
  //exception
  if (!lua_isstring(pL, 1))
  {
    std::string err("<PopLuaString> Cannot retrieve: ");

    throw std::runtime_error(err + name);
  }

  //grab the value, cast to the correct type and return
  std::string s = lua_tostring(pL, 1);

  //remove the value from the stack
  lua_pop(pL, 1);

  return s;
}

//--------------------------- PopLuaBool ------------------------------------
//-----------------------------------------------------------------------------
inline bool PopLuaBool(lua_State* pL, const char* name)
{
  lua_settop(pL, 0);

  lua_getglobal(pL, name);

  //check that the variable is the correct type. If it is not throw an
  //exception
  if (!lua_isstring(pL, 1))
  {
    std::string err("<PopLuaBool> Cannot retrieve: ");

    throw std::runtime_error(err + name);
  }

  //grab the value, cast to the correct type and return
  bool b = lua_toboolean(pL, 1);

  //remove the value from the stack
  lua_pop(pL, 1);

  return b;
}

//------------------------- LuaPopStringFieldFromTable ------------------------
//-----------------------------------------------------------------------------
inline std::string LuaPopStringFieldFromTable(lua_State* L, const char* key)
{

  //push the key onto the stack
  lua_pushstring(L, key);

  //table is now at -2 (key is at -1). lua_gettable now pops the key off
  //the stack and then puts the data found at the key location on the stack
  lua_gettable(L, -2);

  //check that the variable is the correct type. If it is not throw an
  //exception
  if (!lua_isstring(L, -1))
  {
    std::string err("<LuaPopStringFieldFromTable> Cannot retrieve: ");

    throw std::runtime_error(err + key);
  }

  //grab the data
  std::string s = lua_tostring(L, -1);

  lua_pop(L, 1);

  return s;
}

//----------------------------- LuaPopNumberFieldFromTable --------------------
//-----------------------------------------------------------------------------
template <class T>
inline T LuaPopNumberFieldFromTable(lua_State* L, const char* key)
{
  //push the key onto the stack
  lua_pushstring(L, key);

  //table is now at -2 (key is at -1). lua_gettable now pops the key off
  //the stack and then puts the data found at the key location on the stack
  lua_gettable(L, -2);

  //check that the variable is the correct type. If it is not throw an
  //exception
  if (!lua_isnumber(L, -1))
  {
    std::string err("<LuaPopNumberFieldFromTable> Cannot retrieve: ");

    throw std::runtime_error(err + key);
  }

  //grab the data
  T val = (T)lua_tonumber(L, -1);

  lua_pop(L, 1);

  return val;
}



#endif