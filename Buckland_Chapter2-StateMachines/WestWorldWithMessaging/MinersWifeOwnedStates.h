#ifndef MINERSWIFE_OWNED_STATES_H
#define MINERSWIFE_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinersWifeOwnedStates.h
//
//  Desc:   All the states that can be assigned to the MinersWife class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class MinersWife;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class WifesGlobalState : public State<MinersWife>
{  
private:
  
  WifesGlobalState(){}

  //copy ctor and assignment should be private
  WifesGlobalState(const WifesGlobalState&);
  WifesGlobalState& operator=(const WifesGlobalState&);
 
public:

  //this is a singleton
  static WifesGlobalState* Instance();
  
  virtual void Enter(MinersWife* wife){}

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife){}

  virtual bool OnMessage(MinersWife* wife, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouseWork : public State<MinersWife>
{
private:

  DoHouseWork(){}
  
  //copy ctor and assignment should be private
  DoHouseWork(const DoHouseWork&);
  DoHouseWork& operator=(const DoHouseWork&);

public:

  //this is a singleton
  static DoHouseWork* Instance();
  
  virtual void Enter(MinersWife* wife);

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife);
  
  virtual bool OnMessage(MinersWife* wife, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom : public State<MinersWife>
{
private:
  
  VisitBathroom(){}

  //copy ctor and assignment should be private
  VisitBathroom(const VisitBathroom&);
  VisitBathroom& operator=(const VisitBathroom&);
 
public:

  //this is a singleton
  static VisitBathroom* Instance();
  
  virtual void Enter(MinersWife* wife);

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife);

  virtual bool OnMessage(MinersWife* wife, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CookStew : public State<MinersWife>
{
private:
  
  CookStew(){}

  //copy ctor and assignment should be private
  CookStew(const CookStew&);
  CookStew& operator=(const CookStew&);
 
public:

  //this is a singleton
  static CookStew* Instance();
  
  virtual void Enter(MinersWife* wife);

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife);

  virtual bool OnMessage(MinersWife* wife, const Telegram& msg);
};


#endif