#include "Miner.h"
#include "misc/ConsoleUtils.h"


//-----------------------------------------------------------------------------
void Miner::Update()
{
  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);

  m_iThirst += 1;
  
  m_pStateMachine->Update();
}

//-----------------------------------------------------------------------------
void Miner::AddToGoldCarried(const int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

//-----------------------------------------------------------------------------
void Miner::AddToWealth(const int val)
{
  m_iMoneyInBank += val;

  if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

//-----------------------------------------------------------------------------
bool Miner::Thirsty()const
{
  if (m_iThirst >= ThirstLevel){return true;}

  return false;
}


//-----------------------------------------------------------------------------
bool Miner::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}