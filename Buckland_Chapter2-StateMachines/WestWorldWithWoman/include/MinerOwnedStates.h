#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "State.h"


class Miner;



//------------------------------------------------------------------------
//
//  In this state the miner will walk to a goldmine and pick up a nugget
//  of gold. If the miner already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class EnterMineAndDigForNugget : public State<Miner>
{
private:
  
  EnterMineAndDigForNugget(){}
  
  //copy ctor and assignment should be private
  EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
  EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);
 
public:

  static EnterMineAndDigForNugget* Instance();
  
public:
  
  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);

};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  miner is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class VisitBankAndDepositGold : public State<Miner>
{
private:
  
  VisitBankAndDepositGold(){}

  //copy ctor and assignment should be private
  VisitBankAndDepositGold(const VisitBankAndDepositGold&);
  VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);
 
public:

  static VisitBankAndDepositGold* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);
};


//------------------------------------------------------------------------
//
//  miner will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleepTilRested : public State<Miner>
{
private:
  
  GoHomeAndSleepTilRested(){}

  //copy ctor and assignment should be private
  GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
  GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);
 
public:

  static GoHomeAndSleepTilRested* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);
};


//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class QuenchThirst : public State<Miner>
{
private:
  
  QuenchThirst(){}

  //copy ctor and assignment should be private
  QuenchThirst(const QuenchThirst&);
  QuenchThirst& operator=(const QuenchThirst&);
 
public:

  static QuenchThirst* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);
};





#endif