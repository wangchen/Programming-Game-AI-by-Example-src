#include "Goal_Wander.h"
#include "..\Raven_Bot.h"
#include "..\Raven_SteeringBehaviors.h"





//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_Wander::Activate()
{
  m_iStatus = active;

  m_pOwner->GetSteering()->WanderOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Wander::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Wander::Terminate()
{
  m_pOwner->GetSteering()->WanderOff();
}

