#ifndef GOAL_DODGE_SIDE_H
#define GOAL_DODGE_SIDE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_DodgeSideToSide.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   this goal makes the bot dodge from side to side
//
//-----------------------------------------------------------------------------
#include "Goals/Goal.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"





class Goal_DodgeSideToSide : public Goal<Raven_Bot>
{
private:

  Vector2D    m_vStrafeTarget;

  bool        m_bClockwise;

  Vector2D  GetStrafeTarget()const;


public:

  Goal_DodgeSideToSide(Raven_Bot* pBot):Goal<Raven_Bot>(pBot, goal_strafe),
                                        m_bClockwise(RandBool())
  {}


  void Activate();

  int  Process();

  void Render();

  void Terminate();
 
};






#endif
