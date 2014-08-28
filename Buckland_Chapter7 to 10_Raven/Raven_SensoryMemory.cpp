#include "Raven_SensoryMemory.h"
#include "Raven_Game.h"
#include "time/crudetimer.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"

//------------------------------- ctor ----------------------------------------
//-----------------------------------------------------------------------------
 Raven_SensoryMemory:: Raven_SensoryMemory(Raven_Bot* owner,
                                           double MemorySpan):m_pOwner(owner),
                                                            m_dMemorySpan(MemorySpan)
                                                          
{}

//--------------------- MakeNewRecordIfNotAlreadyPresent ----------------------

void Raven_SensoryMemory::MakeNewRecordIfNotAlreadyPresent(Raven_Bot* pOpponent)
{
  //else check to see if this Opponent already exists in the memory. If it doesn't,
  //create a new record
  if (m_MemoryMap.find(pOpponent) == m_MemoryMap.end())
  {
    m_MemoryMap[pOpponent] = MemoryRecord();
  }
}

//------------------------ RemoveBotFromMemory --------------------------------
//
//  this removes a bot's record from memory
//-----------------------------------------------------------------------------
void Raven_SensoryMemory::RemoveBotFromMemory(Raven_Bot* pBot)
{
  MemoryMap::iterator record = m_MemoryMap.find(pBot);
  
  if (record != m_MemoryMap.end())
  {
    m_MemoryMap.erase(record);
  }
}
  
//----------------------- UpdateWithSoundSource -------------------------------
//
// this updates the record for an individual opponent. Note, there is no need to
// test if the opponent is within the FOV because that test will be done when the
// UpdateVision method is called
//-----------------------------------------------------------------------------
void Raven_SensoryMemory::UpdateWithSoundSource(Raven_Bot* pNoiseMaker)
{
  //make sure the bot being examined is not this bot
  if (m_pOwner != pNoiseMaker)
  {
    //if the bot is already part of the memory then update its data, else
    //create a new memory record and add it to the memory
    MakeNewRecordIfNotAlreadyPresent(pNoiseMaker);

    MemoryRecord& info = m_MemoryMap[pNoiseMaker];

    //test if there is LOS between bots 
    if (m_pOwner->GetWorld()->isLOSOkay(m_pOwner->Pos(), pNoiseMaker->Pos()))
    {
      info.bShootable = true;
      
     //record the position of the bot
      info.vLastSensedPosition = pNoiseMaker->Pos();
    }
    else
    {
      info.bShootable = false;
    }
    
    //record the time it was sensed
    info.fTimeLastSensed = (double)Clock->GetCurrentTime();
  }
}

//----------------------------- UpdateVision ----------------------------------
//
//  this method iterates through all the bots in the game world to test if
//  they are in the field of view. Each bot's memory record is updated
//  accordingly
//-----------------------------------------------------------------------------
void Raven_SensoryMemory::UpdateVision()
{
  //for each bot in the world test to see if it is visible to the owner of
  //this class
  const std::list<Raven_Bot*>& bots = m_pOwner->GetWorld()->GetAllBots();
  std::list<Raven_Bot*>::const_iterator curBot;
  for (curBot = bots.begin(); curBot!=bots.end(); ++curBot)
  {
    //make sure the bot being examined is not this bot
    if (m_pOwner != *curBot)
    {
      //make sure it is part of the memory map
      MakeNewRecordIfNotAlreadyPresent(*curBot);

      //get a reference to this bot's data
      MemoryRecord& info = m_MemoryMap[*curBot];

      //test if there is LOS between bots 
      if (m_pOwner->GetWorld()->isLOSOkay(m_pOwner->Pos(), (*curBot)->Pos()))
      {
        info.bShootable = true;

              //test if the bot is within FOV
        if (isSecondInFOVOfFirst(m_pOwner->Pos(),
                                 m_pOwner->Facing(),
                                 (*curBot)->Pos(),
                                  m_pOwner->FieldOfView()))
        {
          info.fTimeLastSensed     = Clock->GetCurrentTime();
          info.vLastSensedPosition = (*curBot)->Pos();
          info.fTimeLastVisible    = Clock->GetCurrentTime();

          if (info.bWithinFOV == false)
          {
            info.bWithinFOV           = true;
            info.fTimeBecameVisible    = info.fTimeLastSensed;
          
          }
        }

        else
        {
          info.bWithinFOV = false;         
        }
      }

      else
      {
        info.bShootable = false;
        info.bWithinFOV = false;
      }
    }
  }//next bot
}


//------------------------ GetListOfRecentlySensedOpponents -------------------
//
//  returns a list of the bots that have been sensed recently
//-----------------------------------------------------------------------------
std::list<Raven_Bot*> 
Raven_SensoryMemory::GetListOfRecentlySensedOpponents()const
{
  //this will store all the opponents the bot can remember
  std::list<Raven_Bot*> opponents;

  double CurrentTime = Clock->GetCurrentTime();

  MemoryMap::const_iterator curRecord = m_MemoryMap.begin();
  for (curRecord; curRecord!=m_MemoryMap.end(); ++curRecord)
  {
    //if this bot has been updated in the memory recently, add to list
    if ( (CurrentTime - curRecord->second.fTimeLastSensed) <= m_dMemorySpan)
    {
      opponents.push_back(curRecord->first);
    }
  }

  return opponents;
}

//----------------------------- isOpponentShootable --------------------------------
//
//  returns true if the bot given as a parameter can be shot (ie. its not
//  obscured by walls)
//-----------------------------------------------------------------------------
bool Raven_SensoryMemory::isOpponentShootable(Raven_Bot* pOpponent)const
{
  MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);
 
  if (it != m_MemoryMap.end())
  {
    return it->second.bShootable;
  }

  return false;
}

//----------------------------- isOpponentWithinFOV --------------------------------
//
//  returns true if the bot given as a parameter is within FOV
//-----------------------------------------------------------------------------
bool  Raven_SensoryMemory::isOpponentWithinFOV(Raven_Bot* pOpponent)const
{
  MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);
 
  if (it != m_MemoryMap.end())
  {
    return it->second.bWithinFOV;
  }

  return false;
}

//---------------------------- GetLastRecordedPositionOfOpponent -------------------
//
//  returns the last recorded position of the bot
//-----------------------------------------------------------------------------
Vector2D  Raven_SensoryMemory::GetLastRecordedPositionOfOpponent(Raven_Bot* pOpponent)const
{
  MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);
 
  if (it != m_MemoryMap.end())
  {
    return it->second.vLastSensedPosition;
  }

  throw std::runtime_error("< Raven_SensoryMemory::GetLastRecordedPositionOfOpponent>: Attempting to get position of unrecorded bot");
}

//----------------------------- GetTimeOpponentHasBeenVisible ----------------------
//
//  returns the amount of time the given bot has been visible
//-----------------------------------------------------------------------------
double  Raven_SensoryMemory::GetTimeOpponentHasBeenVisible(Raven_Bot* pOpponent)const
{
  MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);
 
  if (it != m_MemoryMap.end() && it->second.bWithinFOV)
  {
    return Clock->GetCurrentTime() - it->second.fTimeBecameVisible;
  }

  return 0;
}

//-------------------- GetTimeOpponentHasBeenOutOfView ------------------------
//
//  returns the amount of time the given opponent has remained out of view
//  returns a high value if opponent has never been seen or not present
//-----------------------------------------------------------------------------
double Raven_SensoryMemory::GetTimeOpponentHasBeenOutOfView(Raven_Bot* pOpponent)const
{
  MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);
 
  if (it != m_MemoryMap.end())
  {
    return Clock->GetCurrentTime() - it->second.fTimeLastVisible;
  }

  return MaxDouble;
}

//------------------------ GetTimeSinceLastSensed ----------------------
//
//  returns the amount of time the given bot has been visible
//-----------------------------------------------------------------------------
double  Raven_SensoryMemory::GetTimeSinceLastSensed(Raven_Bot* pOpponent)const
{
  MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);
 
  if (it != m_MemoryMap.end() && it->second.bWithinFOV)
  {
    return Clock->GetCurrentTime() - it->second.fTimeLastSensed;
  }

  return 0;
}

//---------------------- RenderBoxesAroundRecentlySensed ----------------------
//
//  renders boxes around the opponents it has sensed recently.
//-----------------------------------------------------------------------------
void  Raven_SensoryMemory::RenderBoxesAroundRecentlySensed()const
{
  std::list<Raven_Bot*> opponents = GetListOfRecentlySensedOpponents();
  std::list<Raven_Bot*>::const_iterator it;
  for (it = opponents.begin(); it != opponents.end(); ++it)
  {
    gdi->OrangePen();
    Vector2D p = (*it)->Pos();
    double   b = (*it)->BRadius();
      
    gdi->Line(p.x-b, p.y-b, p.x+b, p.y-b);
    gdi->Line(p.x+b, p.y-b, p.x+b, p.y+b);
    gdi->Line(p.x+b, p.y+b, p.x-b, p.y+b);
    gdi->Line(p.x-b, p.y+b, p.x-b, p.y-b);
  }

}