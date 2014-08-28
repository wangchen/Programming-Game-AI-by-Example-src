#ifndef HEALTH_GIVER_H
#define HEALTH_GIVER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:     Trigger_HealthGiver.h
//
//  Author:   Mat Buckland
//
//  Desc:     If a bot runs over an instance of this class its health is
//            increased. 
//
//-----------------------------------------------------------------------------
#include "Triggers/Trigger_Respawning.h"
#include "Triggers/TriggerRegion.h"
#include <iosfwd>
#include "../Raven_Bot.h"



class Trigger_HealthGiver : public Trigger_Respawning<Raven_Bot>
{
private:

  //the amount of health an entity receives when it runs over this trigger
  int   m_iHealthGiven;
  
public:

  Trigger_HealthGiver(std::ifstream& datafile);

  //if triggered, the bot's health will be incremented
  void Try(Raven_Bot* pBot);
  
  //draws a box with a red cross at the trigger's location
  void Render();

  void Read (std::ifstream& is);
};



#endif