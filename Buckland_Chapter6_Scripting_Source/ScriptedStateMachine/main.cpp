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

#include "Entity.h"
#include "Miner.h"
#include "LuaHelperFunctions.h"
#include "ScriptedStateMachine.h"


void RegisterScriptedStateMachineWithLua(lua_State* pLua)
{
  luabind::module(pLua)
    [
      class_<ScriptedStateMachine<Miner> >("ScriptedStateMachine")
    
        .def("ChangeState", &ScriptedStateMachine<Miner>::ChangeState)
        .def("CurrentState", &ScriptedStateMachine<Miner>::CurrentState)
        .def("SetCurrentState", &ScriptedStateMachine<Miner>::SetCurrentState)
    ];  
}


void RegisterEntityWithLua(lua_State* pLua)
{
  module(pLua)
    [
      class_<Entity>("Entity")

        .def("Name", &Entity::Name)
        .def("ID", &Entity::ID)   
    ];  
}


void RegisterMinerWithLua(lua_State* pLua)
{
  module(pLua)
    [   
      class_<Miner, bases<Entity> >("Miner")

        .def("GoldCarried", &Miner::GoldCarried)
        .def("SetGoldCarried", &Miner::SetGoldCarried)
        .def("AddToGoldCarried", &Miner::AddToGoldCarried)
        .def("Fatigued", &Miner::Fatigued)
        .def("DecreaseFatigue", &Miner::DecreaseFatigue)
        .def("IncreaseFatigue", &Miner::IncreaseFatigue) 
        .def("GetFSM", &Miner::GetFSM)
    ];  
}



int main()
{
  //create a lua state
  lua_State* pLua = lua_open();

  LuaExceptionGuard guard(pLua);

  //open the libraries
  OpenLuaLibraries(pLua);
  
  //open luabind
  open(pLua);
  
  //bind the relevant classes to Lua
  RegisterEntityWithLua(pLua);
  RegisterScriptedStateMachineWithLua(pLua);
  RegisterMinerWithLua(pLua);
 
  //load and run the script
  RunLuaScript(pLua, "StateMachineScript.lua");
  
  //create a miner
  Miner bob("bob");

  //grab the global table from the lua state. This will inlclude
  //all the functions and variables defined in the scripts run so far
  //(StateMachineScript.lua in this example)
  object states = get_globals(pLua);

  //make sure Bob's CurrentState object is set to a valid state.
  bob.GetFSM()->SetCurrentState(states["State_GoHome"]);

  //run him through a few update cycles
  for (int i=0; i<10; ++i)
  {
    bob.Update();
  }

  return 0;
}


