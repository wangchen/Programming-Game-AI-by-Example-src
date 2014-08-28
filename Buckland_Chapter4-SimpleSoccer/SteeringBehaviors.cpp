#include "SteeringBehaviors.h"
#include "PlayerBase.h"
#include "2D/Transformations.h"
#include "misc/utils.h"
#include "SoccerTeam.h"
#include "misc/autolist.h"
#include "ParamLoader.h"
#include "SoccerBall.h"


using std::string;
using std::vector;

//------------------------- ctor -----------------------------------------
//
//------------------------------------------------------------------------
SteeringBehaviors::SteeringBehaviors(PlayerBase*  agent,
                                     SoccerPitch* world,
                                     SoccerBall*  ball):
                                  
             m_pPlayer(agent),
             m_iFlags(0),
             m_dMultSeparation(Prm.SeparationCoefficient),
             m_bTagged(false),
             m_dViewDistance(Prm.ViewDistance),
             m_pBall(ball),
             m_dInterposeDist(0.0),
             m_Antenna(5,Vector2D())
{
}

//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool SteeringBehaviors::AccumulateForce(Vector2D &sf, Vector2D ForceToAdd)
{
  //first calculate how much steering force we have left to use
  double MagnitudeSoFar = sf.Length();

  double magnitudeRemaining = m_pPlayer->MaxForce() - MagnitudeSoFar;

  //return false if there is no more force left to use
  if (magnitudeRemaining <= 0.0) return false;

  //calculate the magnitude of the force we want to add
  double MagnitudeToAdd = ForceToAdd.Length();
  
  //now calculate how much of the force we can really add  
  if (MagnitudeToAdd > magnitudeRemaining)
  {
    MagnitudeToAdd = magnitudeRemaining;
  }

  //add it to the steering force
  sf += (Vec2DNormalize(ForceToAdd) * MagnitudeToAdd); 
  
  return true;
}

//---------------------- Calculate ---------------------------------------
//
//  calculates the overall steering force based on the currently active
//  steering behaviors. 
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::Calculate()
{                                                                         
  //reset the force
  m_vSteeringForce.Zero();

  //this will hold the value of each individual steering force
  m_vSteeringForce = SumForces();

  //make sure the force doesn't exceed the vehicles maximum allowable
  m_vSteeringForce.Truncate(m_pPlayer->MaxForce());

  return m_vSteeringForce;
}

//-------------------------- SumForces -----------------------------------
//
//  this method calls each active steering behavior and acumulates their
//  forces until the max steering force magnitude is reached at which
//  time the function returns the steering force accumulated to that 
//  point
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::SumForces()
{
   Vector2D force;
  
  //the soccer players must always tag their neighbors
   FindNeighbours();

  if (On(separation))
  {
    force += Separation() * m_dMultSeparation;

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }    

  if (On(seek))
  {
    force += Seek(m_vTarget);

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

  if (On(arrive))
  {
    force += Arrive(m_vTarget, fast);

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

  if (On(pursuit))
  {
    force += Pursuit(m_pBall);

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

  if (On(interpose))
  {
    force += Interpose(m_pBall, m_vTarget, m_dInterposeDist);

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

  return m_vSteeringForce;
}

//------------------------- ForwardComponent -----------------------------
//
//  calculates the forward component of the steering force
//------------------------------------------------------------------------
double SteeringBehaviors::ForwardComponent()
{
  return m_pPlayer->Heading().Dot(m_vSteeringForce);
}

//--------------------------- SideComponent ------------------------------
//
//  //  calculates the side component of the steering force
//------------------------------------------------------------------------
double SteeringBehaviors::SideComponent()
{
  return m_pPlayer->Side().Dot(m_vSteeringForce) * m_pPlayer->MaxTurnRate();
}


//------------------------------- Seek -----------------------------------
//
//  Given a target, this behavior returns a steering force which will
//  allign the agent with the target and move the agent in the desired
//  direction
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::Seek(Vector2D target)
{
 
  Vector2D DesiredVelocity = Vec2DNormalize(target - m_pPlayer->Pos())
                            * m_pPlayer->MaxSpeed();

  return (DesiredVelocity - m_pPlayer->Velocity());
}


//--------------------------- Arrive -------------------------------------
//
//  This behavior is similar to seek but it attempts to arrive at the
//  target with a zero velocity
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::Arrive(Vector2D    target,
                                   Deceleration deceleration)
{
  Vector2D ToTarget = target - m_pPlayer->Pos();

  //calculate the distance to the target
  double dist = ToTarget.Length();

  if (dist > 0)
  {
    //because Deceleration is enumerated as an int, this value is required
    //to provide fine tweaking of the deceleration..
    const double DecelerationTweaker = 0.3;

    //calculate the speed required to reach the target given the desired
    //deceleration
    double speed =  dist / ((double)deceleration * DecelerationTweaker);                    

    //make sure the velocity does not exceed the max
    speed = min(speed, m_pPlayer->MaxSpeed());

    //from here proceed just like Seek except we don't need to normalize 
    //the ToTarget vector because we have already gone to the trouble
    //of calculating its length: dist. 
    Vector2D DesiredVelocity =  ToTarget * speed / dist;

    return (DesiredVelocity - m_pPlayer->Velocity());
  }

  return Vector2D(0,0);
}


//------------------------------ Pursuit ---------------------------------
//
//  this behavior creates a force that steers the agent towards the 
//  ball
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::Pursuit(const SoccerBall* ball)
{
  Vector2D ToBall = ball->Pos() - m_pPlayer->Pos();
 
  //the lookahead time is proportional to the distance between the ball
  //and the pursuer; 
  double LookAheadTime = 0.0;

  if (ball->Speed() != 0.0)
  {
    LookAheadTime = ToBall.Length() / ball->Speed();
  }

  //calculate where the ball will be at this time in the future
  m_vTarget = ball->FuturePosition(LookAheadTime);

  //now seek to the predicted future position of the ball
  return Arrive(m_vTarget, fast);
}


//-------------------------- FindNeighbours ------------------------------
//
//  tags any vehicles within a predefined radius
//------------------------------------------------------------------------
void SteeringBehaviors::FindNeighbours()
{
  std::list<PlayerBase*>& AllPlayers = AutoList<PlayerBase>::GetAllMembers();
  std::list<PlayerBase*>::iterator curPlyr;
  for (curPlyr = AllPlayers.begin(); curPlyr!=AllPlayers.end(); ++curPlyr)
  {
    //first clear any current tag
    (*curPlyr)->Steering()->UnTag();

    //work in distance squared to avoid sqrts
    Vector2D to = (*curPlyr)->Pos() - m_pPlayer->Pos();

    if (to.LengthSq() < (m_dViewDistance * m_dViewDistance))
    {
      (*curPlyr)->Steering()->Tag();
    }
  }//next
}


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::Separation()
{  
   //iterate through all the neighbors and calculate the vector from the
  Vector2D SteeringForce;
  
  std::list<PlayerBase*>& AllPlayers = AutoList<PlayerBase>::GetAllMembers();
  std::list<PlayerBase*>::iterator curPlyr;
  for (curPlyr = AllPlayers.begin(); curPlyr!=AllPlayers.end(); ++curPlyr)
  {
    //make sure this agent isn't included in the calculations and that
    //the agent is close enough
    if((*curPlyr != m_pPlayer) && (*curPlyr)->Steering()->Tagged())
    {
      Vector2D ToAgent = m_pPlayer->Pos() - (*curPlyr)->Pos();

      //scale the force inversely proportional to the agents distance  
      //from its neighbor.
      SteeringForce += Vec2DNormalize(ToAgent)/ToAgent.Length();
    }
  }

  return SteeringForce;
}

  
//--------------------------- Interpose ----------------------------------
//
//  Given an opponent and an object position this method returns a 
//  force that attempts to position the agent between them
//------------------------------------------------------------------------
Vector2D SteeringBehaviors::Interpose(const SoccerBall* ball,
                                      Vector2D  target,
                                      double     DistFromTarget)
{
  return Arrive(target + Vec2DNormalize(ball->Pos() - target) * 
                DistFromTarget, normal);
}


//----------------------------- RenderAids -------------------------------
//
//------------------------------------------------------------------------
void SteeringBehaviors::RenderAids( )
{ 
  //render the steering force
  gdi->RedPen();

  gdi->Line(m_pPlayer->Pos(), m_pPlayer->Pos() + m_vSteeringForce * 20);


  
}


