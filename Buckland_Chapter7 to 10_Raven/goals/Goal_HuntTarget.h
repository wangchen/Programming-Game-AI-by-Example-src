#ifndef GOAL_FIND_TARGET_H
#define GOAL_FIND_TARGET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_HuntTarget.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Causes a bot to search for its current target. Exits when target
//          is in view
//-----------------------------------------------------------------------------
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"


class Goal_HuntTarget : public Goal_Composite<Raven_Bot>
{
private:

  //this value is set to true if the last visible position of the target
  //bot has been searched without success
  bool  m_bLVPTried;

public:

  Goal_HuntTarget(Raven_Bot* pBot):Goal_Composite<Raven_Bot>(pBot, goal_hunt_target),
                                   m_bLVPTried(false)
  {}

   //the usual suspects
  void Activate();
  int  Process();
  void Terminate(){}

  void Render();


};





#endif
