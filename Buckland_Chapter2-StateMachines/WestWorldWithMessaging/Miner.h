#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinerOwnedStates.h"
#include "fsm/StateMachine.h"

class State;
struct Telegram;

//the amount of gold a miner must have before he feels he can go home
const int ComfortLevel       = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets         = 3;
//above this value a miner is thirsty
const int ThirstLevel        = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;



class Miner : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Miner>*  m_pStateMachine;

  location_type         m_Location;

  //how many nuggets the miner has in his pockets
  int                   m_iGoldCarried;

  int                   m_iMoneyInBank;

  //the higher the value, the thirstier the miner
  int                   m_iThirst;

  //the higher the value, the more tired the miner
  int                   m_iFatigue;

public:

  Miner(int id):m_Location(shack),
                          m_iGoldCarried(0),
                          m_iMoneyInBank(0),
                          m_iThirst(0),
                          m_iFatigue(0),
                          BaseGameEntity(id)

  {
    //set up state machine
    m_pStateMachine = new StateMachine<Miner>(this);

    m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
  }

  ~Miner(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);


  StateMachine<Miner>* GetFSM()const{return m_pStateMachine;}



  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}

  int           GoldCarried()const{return m_iGoldCarried;}
  void          SetGoldCarried(int val){m_iGoldCarried = val;}
  void          AddToGoldCarried(int val);
  bool          PocketsFull()const{return m_iGoldCarried >= MaxNuggets;}

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  int           Wealth()const{return m_iMoneyInBank;}
  void          SetWealth(int val){m_iMoneyInBank = val;}
  void          AddToWealth(int val);

  bool          Thirsty()const;
  void          BuyAndDrinkAWhiskey(){m_iThirst = 0; m_iMoneyInBank-=2;}

};



#endif
