#ifndef GOAL_ATTACKTARGET_H
#define GOAL_ATTACKTARGET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_AttackTarget.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   
//
//-----------------------------------------------------------------------------
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"





class Goal_AttackTarget : public Goal_Composite<Raven_Bot>
{
public:

  Goal_AttackTarget(Raven_Bot* pOwner):Goal_Composite<Raven_Bot>(pOwner, goal_attack_target)
  {}

  void Activate();

  int  Process();

  void Terminate(){m_iStatus = completed;}

};






#endif
