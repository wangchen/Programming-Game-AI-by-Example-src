#include "Miner.h"


Miner::Miner(std::string    name):m_iGoldCarried(0),
                                  m_iFatigue(0),
                                  Entity(name)
                               
{
  m_pStateMachine = new ScriptedStateMachine<Miner>(this);
}

void Miner::AddToGoldCarried(int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}


void Miner::Update()
{
  m_pStateMachine->Update(); 
}

bool Miner::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}