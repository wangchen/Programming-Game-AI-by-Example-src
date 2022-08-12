#include "Projectile_Pellet.h"
#include "../lua/Raven_Scriptor.h"
#include "misc/cgdi.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"
#include "game/EntityFunctionTemplates.h"
#include "../constants.h"
#include "2d/WallIntersectionTests.h"
#include "../Raven_Map.h"
#include <list>

#include "../Raven_Messages.h"
#include "Messaging/MessageDispatcher.h"



//-------------------------- ctor ---------------------------------------------
//-----------------------------------------------------------------------------
Pellet::Pellet(Raven_Bot* shooter, Vector2D target):

        Raven_Projectile(target,
                         shooter->GetWorld(),
                         shooter->ID(),
                         shooter->Pos(),
                         shooter->Facing(),
                         script->GetInt("Pellet_Damage"),
                         script->GetDouble("Pellet_Scale"),
                         script->GetDouble("Pellet_MaxSpeed"),
                         script->GetDouble("Pellet_Mass"),
                         script->GetDouble("Pellet_MaxForce")),

        m_dTimeShotIsVisible(script->GetDouble("Pellet_Persistance"))
{
  
}

//------------------------------ Update ---------------------------------------
        

void Pellet::Update()
{
  if (!HasImpacted())
  {
     //calculate the steering force
    Vector2D DesiredVelocity = Vec2DNormalize(m_vTarget - Pos()) * MaxSpeed();

    Vector2D sf = DesiredVelocity - Velocity();

    //update the position
    Vector2D accel = sf / m_dMass;

    m_vVelocity += accel;

    //make sure vehicle does not exceed maximum velocity
    m_vVelocity.Truncate(m_dMaxSpeed);

    //update the position
    m_vPosition += m_vVelocity; 

    TestForImpact();
  }
  else if (!isVisibleToPlayer())
  {
    m_bDead = true;
  }
}

//----------------------------------- TestForImpact ---------------------------
void Pellet::TestForImpact()
{
  //a shot gun shell is an instantaneous projectile so it only gets the chance
  //to update once 
  m_bImpacted = true;

  //first find the closest wall that this ray intersects with. Then we
  //can test against all entities within this range.
  double DistToClosestImpact;
  FindClosestPointOfIntersectionWithWalls(m_vOrigin,
                                          m_vPosition,
                                          DistToClosestImpact,
                                          m_vImpactPoint,
                                          m_pWorld->GetMap()->GetWalls());

  //test to see if the ray between the current position of the shell and 
  //the start position intersects with any bots.
  Raven_Bot* hit = GetClosestIntersectingBot(m_vOrigin, m_vPosition);
  
  //if no bots hit just return;
  if (!hit) return;

  //determine the impact point with the bot's bounding circle so that the
  //shell can be rendered properly
  GetLineSegmentCircleClosestIntersectionPoint(m_vOrigin,
                                               m_vImpactPoint,
                                               hit->Pos(),
                                               hit->BRadius(),
                                               m_vImpactPoint);

  //send a message to the bot to let it know it's been hit, and who the
  //shot came from
  Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              m_iShooterID,
                              hit->ID(),
                              Msg_TakeThatMF,
                              (void*)&m_iDamageInflicted);
}

//-------------------------- Render -------------------------------------------
//-----------------------------------------------------------------------------
void Pellet::Render()
{
  if ( isVisibleToPlayer() && m_bImpacted)
  {
    gdi->YellowPen();
    gdi->Line(m_vOrigin, m_vImpactPoint);

    gdi->BrownBrush();
    gdi->Circle(m_vImpactPoint, 3);
  }
}