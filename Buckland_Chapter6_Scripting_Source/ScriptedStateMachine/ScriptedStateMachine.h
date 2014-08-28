#ifndef SCRIPTEDScriptedStateMachine_H
#define SCRIPTEDScriptedStateMachine_H
#pragma warning (disable : 4786)
//------------------------------------------------------------------------
//
//  Name:   ScriptedStateMachine.h
//
//  Desc:   A simple scripted state machine class. Inherit from this class and 
//          create some states in Lua to give your agents FSM functionality
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

extern "C"
{
  #include <lua.h>
}

#include <luabind/luabind.hpp>
#include <cassert>


template <class entity_type>
class ScriptedStateMachine
{

private:

  //pointer to the agent that owns this instance
  entity_type*      m_pOwner;

  //the current state is a lua table of lua functions. A table may be
  //represented in C++ using a luabind::object
  luabind::object   m_CurrentState;
  
public:

  ScriptedStateMachine(entity_type* owner):m_pOwner(owner){}

  //use these methods to initialize the FSM
  void SetCurrentState(const luabind::object& s){m_CurrentState = s;}

  
  //call this to update the FSM
  void  Update()
  {
    //make sure the state is valid before calling its Execute 'method'
    if (m_CurrentState.is_valid())  //this could also be written as 'if(m_CurrentState)'
    { 
      m_CurrentState.at("Execute")(m_pOwner);
    }
  }

  //change to a new state
  void  ChangeState(const luabind::object& new_state)
  {
    //call the exit method of the existing state
    m_CurrentState.at("Exit")(m_pOwner);

    //change state to the new state
    m_CurrentState = new_state;

    //call the entry method of the new state
    m_CurrentState.at("Enter")(m_pOwner);
  }

  //retrieve the current state
  const luabind::object&  CurrentState()const{return m_CurrentState;}
};




#endif


