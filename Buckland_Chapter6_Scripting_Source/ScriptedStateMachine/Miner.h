#ifndef MINER_H
#define MINER_H
#pragma warning (disable : 4786)
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer. The miner has a FSM defined
//          by a Lua script.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>

#include "Entity.h"
#include "ScriptedStateMachine.h"




//the amount of nuggets a miner can carry
const int MaxNuggets         = 3;

//above this value a miner is sleepy
const int TirednessThreshold = 2;



class Miner : public Entity
{
private:

  ScriptedStateMachine<Miner>* m_pStateMachine;

  //how many nuggets the miner has in his pockets
  int                   m_iGoldCarried;

  //the higher the value, the more tired the miner
  int                   m_iFatigue;

public:

  Miner(std::string name);

  ~Miner(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  int           GoldCarried()const{return m_iGoldCarried;}
  void          SetGoldCarried(int val){m_iGoldCarried = val;}
  void          AddToGoldCarried(int val);

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  ScriptedStateMachine<Miner>* GetFSM()const{return m_pStateMachine;}
};



#endif
