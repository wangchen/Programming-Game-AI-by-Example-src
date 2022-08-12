#include "Goal_MoveToPosition.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"
#include "../navigation/Raven_PathPlanner.h"
#include "Messaging/Telegram.h"
#include "../Raven_Messages.h"
#include "misc/cgdi.h"

#include "Goal_SeekToPosition.h"
#include "Goal_FollowPath.h"



//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_MoveToPosition::Activate()
{
  m_iStatus = active;
  
  //make sure the subgoal list is clear.
  RemoveAllSubgoals();

  //requests a path to the target position from the path planner. Because, for
  //demonstration purposes, the Raven path planner uses time-slicing when 
  //processing the path requests the bot may have to wait a few update cycles
  //before a path is calculated. Consequently, for appearances sake, it just
  //seeks directly to the target position whilst it's awaiting notification
  //that the path planning request has succeeded/failed
  if (m_pOwner->GetPathPlanner()->RequestPathToPosition(m_vDestination))
  {
    AddSubgoal(new Goal_SeekToPosition(m_pOwner, m_vDestination));
  }
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_MoveToPosition::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
    
  //process the subgoals
  m_iStatus = ProcessSubgoals();

  //if any of the subgoals have failed then this goal re-plans
  ReactivateIfFailed();

  return m_iStatus;
}

//---------------------------- HandleMessage ----------------------------------
//-----------------------------------------------------------------------------
bool Goal_MoveToPosition::HandleMessage(const Telegram& msg)
{
  //first, pass the message down the goal hierarchy
  bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

  //if the msg was not handled, test to see if this goal can handle it
  if (bHandled == false)
  {
    switch(msg.Msg)
    {
    case Msg_PathReady:

      //clear any existing goals
      RemoveAllSubgoals();

      AddSubgoal(new Goal_FollowPath(m_pOwner,
                                     m_pOwner->GetPathPlanner()->GetPath()));

      return true; //msg handled


    case Msg_NoPathAvailable:

      m_iStatus = failed;

      return true; //msg handled

    default: return false;
    }
  }

  //handled by subgoals
  return true;
}

//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void Goal_MoveToPosition::Render()
{
  //forward the request to the subgoals
  Goal_Composite<Raven_Bot>::Render();
  
  //draw a bullseye
  gdi->BlackPen();
  gdi->BlueBrush();
  gdi->Circle(m_vDestination, 6);
  gdi->RedBrush();
  gdi->RedPen();
  gdi->Circle(m_vDestination, 4);
  gdi->YellowBrush();
  gdi->YellowPen();
  gdi->Circle(m_vDestination, 2);
}

