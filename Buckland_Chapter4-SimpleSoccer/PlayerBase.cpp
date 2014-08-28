#include "PlayerBase.h"
#include "SteeringBehaviors.h"
#include "2D/Transformations.h"
#include "2D/Geometry.h"
#include "misc/Cgdi.h"
#include "2D/C2DMatrix.h"
#include "Game/Region.h"
#include "ParamLoader.h"
#include "Messaging/MessageDispatcher.h"
#include "SoccerMessages.h"
#include "SoccerTeam.h"
#include "ParamLoader.h"
#include "Goal.h"
#include "SoccerBall.h"
#include "SoccerPitch.h"
#include "Debug/DebugConsole.h"


using std::vector;


//----------------------------- dtor -------------------------------------
//------------------------------------------------------------------------
PlayerBase::~PlayerBase()
{
  delete m_pSteering;
}

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
PlayerBase::PlayerBase(SoccerTeam* home_team,
                       int   home_region,
                       Vector2D  heading,
                       Vector2D velocity,
                       double    mass,
                       double    max_force,
                       double    max_speed,
                       double    max_turn_rate,
                       double    scale,
                       player_role role):    

    MovingEntity(home_team->Pitch()->GetRegionFromIndex(home_region)->Center(),
                 scale*10.0,
                 velocity,
                 max_speed,
                 heading,
                 mass,
                 Vector2D(scale,scale),
                 max_turn_rate,
                 max_force),
   m_pTeam(home_team),
   m_dDistSqToBall(MaxFloat),
   m_iHomeRegion(home_region),
   m_iDefaultRegion(home_region),
   m_PlayerRole(role)
{
  
  //setup the vertex buffers and calculate the bounding radius
  const int NumPlayerVerts = 4;
  const Vector2D player[NumPlayerVerts] = {Vector2D(-3, 8),
                                            Vector2D(3,10),
                                            Vector2D(3,-10),
                                            Vector2D(-3,-8)};

  for (int vtx=0; vtx<NumPlayerVerts; ++vtx)
  {
    m_vecPlayerVB.push_back(player[vtx]);

    //set the bounding radius to the length of the 
    //greatest extent
    if (abs(player[vtx].x) > m_dBoundingRadius)
    {
      m_dBoundingRadius = abs(player[vtx].x);
    }

    if (abs(player[vtx].y) > m_dBoundingRadius)
    {
      m_dBoundingRadius = abs(player[vtx].y);
    }
  }

  //set up the steering behavior class
  m_pSteering = new SteeringBehaviors(this,
                                      m_pTeam->Pitch(),
                                      Ball());  
  
  //a player's start target is its start position (because it's just waiting)
  m_pSteering->SetTarget(home_team->Pitch()->GetRegionFromIndex(home_region)->Center());
}




//----------------------------- TrackBall --------------------------------
//
//  sets the player's heading to point at the ball
//------------------------------------------------------------------------
void PlayerBase::TrackBall()
{
  RotateHeadingToFacePosition(Ball()->Pos());  
}

//----------------------------- TrackTarget --------------------------------
//
//  sets the player's heading to point at the current target
//------------------------------------------------------------------------
void PlayerBase::TrackTarget()
{
  SetHeading(Vec2DNormalize(Steering()->Target() - Pos()));
}


//------------------------------------------------------------------------
//
//binary predicates for std::sort (see CanPassForward/Backward)
//------------------------------------------------------------------------
bool  SortByDistanceToOpponentsGoal(const PlayerBase*const p1,
                                    const PlayerBase*const p2)
{
  return (p1->DistToOppGoal() < p2->DistToOppGoal());
}

bool  SortByReversedDistanceToOpponentsGoal(const PlayerBase*const p1,
                                            const PlayerBase*const p2)
{
  return (p1->DistToOppGoal() > p2->DistToOppGoal());
}


//------------------------- WithinFieldOfView ---------------------------
//
//  returns true if subject is within field of view of this player
//-----------------------------------------------------------------------
bool PlayerBase::PositionInFrontOfPlayer(Vector2D position)const
{
  Vector2D ToSubject = position - Pos();

  if (ToSubject.Dot(Heading()) > 0) 
    
    return true;

  else

    return false;
}

//------------------------- IsThreatened ---------------------------------
//
//  returns true if there is an opponent within this player's 
//  comfort zone
//------------------------------------------------------------------------
bool PlayerBase::isThreatened()const
{
  //check against all opponents to make sure non are within this
  //player's comfort zone
  std::vector<PlayerBase*>::const_iterator curOpp;  
  curOpp = Team()->Opponents()->Members().begin();
 
  for (curOpp; curOpp != Team()->Opponents()->Members().end(); ++curOpp)
  {
    //calculate distance to the player. if dist is less than our
    //comfort zone, and the opponent is infront of the player, return true
    if (PositionInFrontOfPlayer((*curOpp)->Pos()) &&
       (Vec2DDistanceSq(Pos(), (*curOpp)->Pos()) < Prm.PlayerComfortZoneSq))
    {        
      return true;
    }
   
  }// next opp

  return false;
}

//----------------------------- FindSupport -----------------------------------
//
//  determines the player who is closest to the SupportSpot and messages him
//  to tell him to change state to SupportAttacker
//-----------------------------------------------------------------------------
void PlayerBase::FindSupport()const
{    
  //if there is no support we need to find a suitable player.
  if (Team()->SupportingPlayer() == NULL)
  {
    PlayerBase* BestSupportPly = Team()->DetermineBestSupportingAttacker();

    Team()->SetSupportingPlayer(BestSupportPly);

    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            ID(),
                            Team()->SupportingPlayer()->ID(),
                            Msg_SupportAttacker,
                            NULL);
  }
    
  PlayerBase* BestSupportPly = Team()->DetermineBestSupportingAttacker();
    
  //if the best player available to support the attacker changes, update
  //the pointers and send messages to the relevant players to update their
  //states
  if (BestSupportPly && (BestSupportPly != Team()->SupportingPlayer()))
  {
    
    if (Team()->SupportingPlayer())
    {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              ID(),
                              Team()->SupportingPlayer()->ID(),
                              Msg_GoHome,
                              NULL);
    }
    
    
    
    Team()->SetSupportingPlayer(BestSupportPly);

    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            ID(),
                            Team()->SupportingPlayer()->ID(),
                            Msg_SupportAttacker,
                            NULL);
  }
}


  //calculate distance to opponent's goal. Used frequently by the passing//methods
double PlayerBase::DistToOppGoal()const
{
  return fabs(Pos().x - Team()->OpponentsGoal()->Center().x);
}

double PlayerBase::DistToHomeGoal()const
{
  return fabs(Pos().x - Team()->HomeGoal()->Center().x);
}

bool PlayerBase::isControllingPlayer()const
{return Team()->ControllingPlayer()==this;}

bool PlayerBase::BallWithinKeeperRange()const
{
  return (Vec2DDistanceSq(Pos(), Ball()->Pos()) < Prm.KeeperInBallRangeSq);
}

bool PlayerBase::BallWithinReceivingRange()const
{
  return (Vec2DDistanceSq(Pos(), Ball()->Pos()) < Prm.BallWithinReceivingRangeSq);
}

bool PlayerBase::BallWithinKickingRange()const
{
  return (Vec2DDistanceSq(Ball()->Pos(), Pos()) < Prm.PlayerKickingDistanceSq);
}


bool PlayerBase::InHomeRegion()const
{
  if (m_PlayerRole == goal_keeper)
  {
    return Pitch()->GetRegionFromIndex(m_iHomeRegion)->Inside(Pos(), Region::normal);
  }
  else
  {
    return Pitch()->GetRegionFromIndex(m_iHomeRegion)->Inside(Pos(), Region::halfsize);
  }
}

bool PlayerBase::AtTarget()const
{
  return (Vec2DDistanceSq(Pos(), Steering()->Target()) < Prm.PlayerInTargetRangeSq);
}

bool PlayerBase::isClosestTeamMemberToBall()const
{
  return Team()->PlayerClosestToBall() == this;
}

bool PlayerBase::isClosestPlayerOnPitchToBall()const
{
  return isClosestTeamMemberToBall() && 
         (DistSqToBall() < Team()->Opponents()->ClosestDistToBallSq());
}

bool PlayerBase::InHotRegion()const
{
  return fabs(Pos().y - Team()->OpponentsGoal()->Center().y ) <
         Pitch()->PlayingArea()->Length()/3.0;
}

bool PlayerBase::isAheadOfAttacker()const
{
  return fabs(Pos().x - Team()->OpponentsGoal()->Center().x) <
         fabs(Team()->ControllingPlayer()->Pos().x - Team()->OpponentsGoal()->Center().x);
}

SoccerBall* const PlayerBase::Ball()const
{
  return Team()->Pitch()->Ball();
}

SoccerPitch* const PlayerBase::Pitch()const
{
  return Team()->Pitch();
}

const Region* const PlayerBase::HomeRegion()const
{
  return Pitch()->GetRegionFromIndex(m_iHomeRegion);
}


