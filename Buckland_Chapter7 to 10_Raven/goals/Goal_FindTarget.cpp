#include "Goal_Wander.h"
#include "..\Raven_Bot.h"
#include "..\Raven_SteeringBehaviors.h"





//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_Wander::Activate()
{
  m_pOwner->GetSteering()->WanderOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Wander::Process()
{
  if (m_Status == inactive)
  {
    Activate();
    m_Status = active;
  }

  return m_Status;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Wander::Terminate()
{
  m_pOwner->GetSteering()->WanderOff();

  m_Status = completed;
}

