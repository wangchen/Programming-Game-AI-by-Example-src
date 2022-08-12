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
#include "State.h"

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

  static WifesGlobalState* Instance();
  
  virtual void Enter(MinersWife* wife){}

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife){}
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

  static DoHouseWork* Instance();
  
  virtual void Enter(MinersWife* wife);

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife);

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

  static VisitBathroom* Instance();
  
  virtual void Enter(MinersWife* wife);

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife);

};


#endif