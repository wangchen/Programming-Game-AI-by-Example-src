#include "Goal_DodgeSideToSide.h"
#include "Goal_SeekToPosition.h"
#include "../Raven_Bot.h"
#include "../Raven_SteeringBehaviors.h"
#include "../Raven_Game.h"

#include "Messaging/Telegram.h"
#include "../Raven_Messages.h"

#include "debug/DebugConsole.h"
#include "misc/cgdi.H"


//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_DodgeSideToSide::Activate()
{
  m_iStatus = active;

  m_pOwner->GetSteering()->SeekOn();

  
    if (m_bClockwise)
    {
      if (m_pOwner->canStepRight(m_vStrafeTarget))
      {
        m_pOwner->GetSteering()->SetTarget(m_vStrafeTarget);
      }
      else
      {
        //debug_con << "changing" << "";
        m_bClockwise = !m_bClockwise;
        m_iStatus = inactive;
      }
    }

    else
    {
      if (m_pOwner->canStepLeft(m_vStrafeTarget))
      {
        m_pOwner->GetSteering()->SetTarget(m_vStrafeTarget);
      }
      else
      {
       // debug_con << "changing" << "";
        m_bClockwise = !m_bClockwise;
        m_iStatus = inactive;
      }
    }

   
}



//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_DodgeSideToSide::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive(); 

  //if target goes out of view terminate
  if (!m_pOwner->GetTargetSys()->isTargetWithinFOV())
  {
    m_iStatus = completed;
  }

  //else if bot reaches the target position set status to inactive so the goal 
  //is reactivated on the next update-step
  else if (m_pOwner->isAtPosition(m_vStrafeTarget))
  {
    m_iStatus = inactive;
  }

  return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_DodgeSideToSide::Terminate()
{
  m_pOwner->GetSteering()->SeekOff();
}

//---------------------------- Render -----------------------------------------

void Goal_DodgeSideToSide::Render()
{
//#define SHOW_TARGET
#ifdef SHOW_TARGET
  gdi->OrangePen();
  gdi->HollowBrush();

  gdi->Line(m_pOwner->Pos(), m_vStrafeTarget);
  gdi->Circle(m_vStrafeTarget, 3);
#endif
  
}



