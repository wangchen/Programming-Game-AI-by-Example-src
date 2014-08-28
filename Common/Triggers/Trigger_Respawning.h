#ifndef Trigger_Respawning_H
#define Trigger_Respawning_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:     Trigger_Respawning.h
//
//  Author:   Mat Buckland
//
//  Desc:     base class to create a trigger that is capable of respawning
//            after a period of inactivity
//
//-----------------------------------------------------------------------------
#include "Trigger.h"
#include <iosfwd>
#include <cassert>


template <class entity_type>
class Trigger_Respawning : public Trigger<entity_type>
{
protected:

  //When a bot comes within this trigger's area of influence it is triggered
  //but then becomes inactive for a specified amount of time. These values
  //control the amount of time required to pass before the trigger becomes 
  //active once more.
  int   m_iNumUpdatesBetweenRespawns;
  int   m_iNumUpdatesRemainingUntilRespawn;

  //sets the trigger to be inactive for m_iNumUpdatesBetweenRespawns 
  //update-steps
  void Deactivate()
  {
    SetInactive();
    m_iNumUpdatesRemainingUntilRespawn = m_iNumUpdatesBetweenRespawns;
  }

public:

  Trigger_Respawning(int id):Trigger<entity_type>(id),
                             m_iNumUpdatesBetweenRespawns(0),
                             m_iNumUpdatesRemainingUntilRespawn(0)
  {}

  virtual ~Trigger_Respawning(){}

  //to be implemented by child classes
  virtual void  Try(entity_type*) = 0;

  //this is called each game-tick to update the trigger's internal state
  virtual void Update()
  {
    if ( (--m_iNumUpdatesRemainingUntilRespawn <= 0) && !isActive())
    {
      SetActive();
    }
  }
  
  void SetRespawnDelay(unsigned int numTicks)
  {m_iNumUpdatesBetweenRespawns = numTicks;}
};




#endif