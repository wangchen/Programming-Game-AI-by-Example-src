 #ifndef STATEMACHINE_H
#define STATEMACHINE_H

//------------------------------------------------------------------------
//
//  Name:   StateMachine.h
//
//  Desc:   State machine class. Inherit from this class and create some 
//          states to give your agents FSM functionality
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <cassert>
#include <string>

#include "State.h"
#include "Messaging/Telegram.h"


template <class entity_type>
class StateMachine
{
private:

  //a pointer to the agent that owns this instance
  entity_type*          m_pOwner;

  State<entity_type>*   m_pCurrentState;
  
  //a record of the last state the agent was in
  State<entity_type>*   m_pPreviousState;

  //this is called every time the FSM is updated
  State<entity_type>*   m_pGlobalState;
  

public:

  StateMachine(entity_type* owner):m_pOwner(owner),
                                   m_pCurrentState(NULL),
                                   m_pPreviousState(NULL),
                                   m_pGlobalState(NULL)
  {}

  virtual ~StateMachine(){}

  //use these methods to initialize the FSM
  void SetCurrentState(State<entity_type>* s){m_pCurrentState = s;}
  void SetGlobalState(State<entity_type>* s) {m_pGlobalState = s;}
  void SetPreviousState(State<entity_type>* s){m_pPreviousState = s;}
  
  //call this to update the FSM
  void  Update()const
  {
    //if a global state exists, call its execute method, else do nothing
    if(m_pGlobalState)   m_pGlobalState->Execute(m_pOwner);

    //same for the current state
    if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
  }

  bool  HandleMessage(const Telegram& msg)const
  {
    //first see if the current state is valid and that it can handle
    //the message
    if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
    {
      return true;
    }
  
    //if not, and if a global state has been implemented, send 
    //the message to the global state
    if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
    {
      return true;
    }

    return false;
  }

  //change to a new state
  void  ChangeState(State<entity_type>* pNewState)
  {
    assert(pNewState && "<StateMachine::ChangeState>:trying to assign null state to current");

    //keep a record of the previous state
    m_pPreviousState = m_pCurrentState;

    //call the exit method of the existing state
    m_pCurrentState->Exit(m_pOwner);

    //change state to the new state
    m_pCurrentState = pNewState;

    //call the entry method of the new state
    m_pCurrentState->Enter(m_pOwner);
  }

  //change state back to the previous state
  void  RevertToPreviousState()
  {
    ChangeState(m_pPreviousState);
  }

  //returns true if the current state's type is equal to the type of the
  //class passed as a parameter. 
  bool  isInState(const State<entity_type>& st)const
  {
    if (typeid(*m_pCurrentState) == typeid(st)) return true;
    return false;
  }

  State<entity_type>*  CurrentState()  const{return m_pCurrentState;}
  State<entity_type>*  GlobalState()   const{return m_pGlobalState;}
  State<entity_type>*  PreviousState() const{return m_pPreviousState;}

  //only ever used during debugging to grab the name of the current state
  std::string         GetNameOfCurrentState()const
  {
    std::string s(typeid(*m_pCurrentState).name());

    //remove the 'class ' part from the front of the string
    if (s.size() > 5)
    {
      s.erase(0, 6);
    }

    return s;
  }
};




#endif


