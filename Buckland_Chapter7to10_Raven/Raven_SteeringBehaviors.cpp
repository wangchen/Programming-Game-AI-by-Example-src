#include "Raven_SteeringBehaviors.h"
#include "Raven_Bot.h"
#include "2d/Wall2D.h"
#include "2d/Transformations.h"
#include "misc/utils.h"
#include "misc/Cgdi.h"
#include "Raven_Game.h"
#include "2d/geometry.h"
#include "lua/Raven_Scriptor.h"
#include "Raven_Map.h"

#include <cassert>


using std::string;
using std::vector;



//------------------------- ctor -----------------------------------------
//
//------------------------------------------------------------------------
Raven_Steering::Raven_Steering(Raven_Game* world, Raven_Bot* agent):
                                  
             m_pWorld(world),
             m_pRaven_Bot(agent),
             m_iFlags(0),
             m_dWeightSeparation(script->GetDouble("SeparationWeight")),
             m_dWeightWander(script->GetDouble("WanderWeight")),
             m_dWeightWallAvoidance(script->GetDouble("WallAvoidanceWeight")),
             m_dViewDistance(script->GetDouble("ViewDistance")),
             m_dWallDetectionFeelerLength(script->GetDouble("WallDetectionFeelerLength")),
             m_Feelers(3),
             m_Deceleration(normal),
             m_pTargetAgent1(NULL),
             m_pTargetAgent2(NULL),
             m_dWanderDistance(WanderDist),
             m_dWanderJitter(WanderJitterPerSec),
             m_dWanderRadius(WanderRad),
             m_dWeightSeek(script->GetDouble("SeekWeight")),
             m_dWeightArrive(script->GetDouble("ArriveWeight")),
             m_bCellSpaceOn(false),
             m_SummingMethod(prioritized)
             


{
  //stuff for the wander behavior
  double theta = RandFloat() * TwoPi;

  //create a vector to a target position on the wander circle
  m_vWanderTarget = Vector2D(m_dWanderRadius * cos(theta),
                              m_dWanderRadius * sin(theta));

}

//---------------------------------dtor ----------------------------------
Raven_Steering::~Raven_Steering(){}


/////////////////////////////////////////////////////////////////////////////// CALCULATE METHODS 


//----------------------- Calculate --------------------------------------
//
//  calculates the accumulated steering force according to the method set
//  in m_SummingMethod
//------------------------------------------------------------------------
Vector2D Raven_Steering::Calculate()
{ 
  //reset the steering force
  m_vSteeringForce.Zero();

  //tag neighbors if any of the following 3 group behaviors are switched on
  if (On(separation))
  {
    m_pWorld->TagRaven_BotsWithinViewRange(m_pRaven_Bot, m_dViewDistance);
  }

  m_vSteeringForce = CalculatePrioritized();

  return m_vSteeringForce;
}

//------------------------- ForwardComponent -----------------------------
//
//  returns the forward oomponent of the steering force
//------------------------------------------------------------------------
double Raven_Steering::ForwardComponent()
{
  return m_pRaven_Bot->Heading().Dot(m_vSteeringForce);
}

//--------------------------- SideComponent ------------------------------
//  returns the side component of the steering force
//------------------------------------------------------------------------
double Raven_Steering::SideComponent()
{
  return m_pRaven_Bot->Side().Dot(m_vSteeringForce);
}


//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool Raven_Steering::AccumulateForce(Vector2D &RunningTot,
                                       Vector2D ForceToAdd)
{  
  //calculate how much steering force the vehicle has used so far
  double MagnitudeSoFar = RunningTot.Length();

  //calculate how much steering force remains to be used by this vehicle
  double MagnitudeRemaining = m_pRaven_Bot->MaxForce() - MagnitudeSoFar;

  //return false if there is no more force left to use
  if (MagnitudeRemaining <= 0.0) return false;

  //calculate the magnitude of the force we want to add
  double MagnitudeToAdd = ForceToAdd.Length();
  
  //if the magnitude of the sum of ForceToAdd and the running total
  //does not exceed the maximum force available to this vehicle, just
  //add together. Otherwise add as much of the ForceToAdd vector is
  //possible without going over the max.
  if (MagnitudeToAdd < MagnitudeRemaining)
  {
    RunningTot += ForceToAdd;
  }

  else
  {
    MagnitudeToAdd = MagnitudeRemaining;

    //add it to the steering force
    RunningTot += (Vec2DNormalize(ForceToAdd) * MagnitudeToAdd); 
  }

  return true;
}



//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and acumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//------------------------------------------------------------------------
Vector2D Raven_Steering::CalculatePrioritized()
{       
  Vector2D force;

  if (On(wall_avoidance))
  {
    force = WallAvoidance(m_pWorld->GetMap()->GetWalls()) *
            m_dWeightWallAvoidance;

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

 
  //these next three can be combined for flocking behavior (wander is
  //also a good behavior to add into this mix)

    if (On(separation))
    {
      force = Separation(m_pWorld->GetAllBots()) * m_dWeightSeparation;

      if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
    }


  if (On(seek))
  {
    force = Seek(m_vTarget) * m_dWeightSeek;

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }


  if (On(arrive))
  {
    force = Arrive(m_vTarget, m_Deceleration) * m_dWeightArrive;

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

  if (On(wander))
  {
    force = Wander() * m_dWeightWander;

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }


  return m_vSteeringForce;
}


/////////////////////////////////////////////////////////////////////////////// START OF BEHAVIORS

//------------------------------- Seek -----------------------------------
//
//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target
//------------------------------------------------------------------------
Vector2D Raven_Steering::Seek(const Vector2D &target)
{
 
  Vector2D DesiredVelocity = Vec2DNormalize(target - m_pRaven_Bot->Pos())
                            * m_pRaven_Bot->MaxSpeed();

  return (DesiredVelocity - m_pRaven_Bot->Velocity());
}


//--------------------------- Arrive -------------------------------------
//
//  This behavior is similar to seek but it attempts to arrive at the
//  target with a zero velocity
//------------------------------------------------------------------------
Vector2D Raven_Steering::Arrive(const Vector2D    &target,
                                const Deceleration deceleration)
{
  Vector2D ToTarget = target - m_pRaven_Bot->Pos();

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
    speed = MinOf(speed, m_pRaven_Bot->MaxSpeed());

    //from here proceed just like Seek except we don't need to normalize 
    //the ToTarget vector because we have already gone to the trouble
    //of calculating its length: dist. 
    Vector2D DesiredVelocity =  ToTarget * speed / dist;

    return (DesiredVelocity - m_pRaven_Bot->Velocity());
  }

  return Vector2D(0,0);
}



//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//------------------------------------------------------------------------
Vector2D Raven_Steering::Wander()
{ 
  //first, add a small random vector to the target's position
  m_vWanderTarget += Vector2D(RandomClamped() * m_dWanderJitter,
                              RandomClamped() * m_dWanderJitter);

  //reproject this new vector back on to a unit circle
  m_vWanderTarget.Normalize();

  //increase the length of the vector to the same as the radius
  //of the wander circle
  m_vWanderTarget *= m_dWanderRadius;

  //move the target into a position WanderDist in front of the agent
  Vector2D target = m_vWanderTarget + Vector2D(m_dWanderDistance, 0);

  //project the target into world space
  Vector2D Target = PointToWorldSpace(target,
                                       m_pRaven_Bot->Heading(),
                                       m_pRaven_Bot->Side(), 
                                       m_pRaven_Bot->Pos());

  //and steer towards it
  return Target - m_pRaven_Bot->Pos(); 
}


//--------------------------- WallAvoidance --------------------------------
//
//  This returns a steering force that will keep the agent away from any
//  walls it may encounter
//------------------------------------------------------------------------
Vector2D Raven_Steering::WallAvoidance(const vector<Wall2D*> &walls)
{
  //the feelers are contained in a std::vector, m_Feelers
  CreateFeelers();
  
  double DistToThisIP    = 0.0;
  double DistToClosestIP = MaxDouble;

  //this will hold an index into the vector of walls
  int ClosestWall = -1;

  Vector2D SteeringForce,
            point,         //used for storing temporary info
            ClosestPoint;  //holds the closest intersection point

  //examine each feeler in turn
  for (unsigned int flr=0; flr<m_Feelers.size(); ++flr)
  {
    //run through each wall checking for any intersection points
    for (unsigned int w=0; w<walls.size(); ++w)
    {
      if (LineIntersection2D(m_pRaven_Bot->Pos(),
                             m_Feelers[flr],
                             walls[w]->From(),
                             walls[w]->To(),
                             DistToThisIP,
                             point))
      {
        //is this the closest found so far? If so keep a record
        if (DistToThisIP < DistToClosestIP)
        {
          DistToClosestIP = DistToThisIP;

          ClosestWall = w;

          ClosestPoint = point;
        }
      }
    }//next wall

  
    //if an intersection point has been detected, calculate a force  
    //that will direct the agent away
    if (ClosestWall >=0)
    {
      //calculate by what distance the projected position of the agent
      //will overshoot the wall
      Vector2D OverShoot = m_Feelers[flr] - ClosestPoint;

      //create a force in the direction of the wall normal, with a 
      //magnitude of the overshoot
      SteeringForce = walls[ClosestWall]->Normal() * OverShoot.Length();
    }

  }//next feeler

  return SteeringForce;
}

//------------------------------- CreateFeelers --------------------------
//
//  Creates the antenna utilized by WallAvoidance
//------------------------------------------------------------------------
void Raven_Steering::CreateFeelers()
{
  //feeler pointing straight in front
  m_Feelers[0] = m_pRaven_Bot->Pos() + m_dWallDetectionFeelerLength *
                 m_pRaven_Bot->Heading() * m_pRaven_Bot->Speed();

  //feeler to left
  Vector2D temp = m_pRaven_Bot->Heading();
  Vec2DRotateAroundOrigin(temp, HalfPi * 3.5);
  m_Feelers[1] = m_pRaven_Bot->Pos() + m_dWallDetectionFeelerLength/2.0 * temp;

  //feeler to right
  temp = m_pRaven_Bot->Heading();
  Vec2DRotateAroundOrigin(temp, HalfPi * 0.5);
  m_Feelers[2] = m_pRaven_Bot->Pos() + m_dWallDetectionFeelerLength/2.0 * temp;
}


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
Vector2D Raven_Steering::Separation(const std::list<Raven_Bot*>& neighbors)
{  
  //iterate through all the neighbors and calculate the vector from the
  Vector2D SteeringForce;

  std::list<Raven_Bot*>::const_iterator it = neighbors.begin();
  for (it; it != neighbors.end(); ++it)
  {
    //make sure this agent isn't included in the calculations and that
    //the agent being examined is close enough. ***also make sure it doesn't
    //include the evade target ***
    if((*it != m_pRaven_Bot) && (*it)->IsTagged() &&
      (*it != m_pTargetAgent1))
    {
      Vector2D ToAgent = m_pRaven_Bot->Pos() - (*it)->Pos();

      //scale the force inversely proportional to the agents distance  
      //from its neighbor.
      SteeringForce += Vec2DNormalize(ToAgent)/ToAgent.Length();
    }
  }

  return SteeringForce;
}























