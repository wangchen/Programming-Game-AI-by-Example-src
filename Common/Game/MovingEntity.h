#ifndef MOVING_ENTITY
#define MOVING_ENTITY
//------------------------------------------------------------------------
//
//  Name:   MovingEntity.h
//
//  Desc:   A base class defining an entity that moves. The entity has 
//          a local coordinate system and members for defining its
//          mass and velocity.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <cassert>

#include "2D/Vector2D.h"
#include "Game/BaseGameEntity.h"



class MovingEntity : public BaseGameEntity
{
protected:
  
  Vector2D    m_vVelocity;
  
  //a normalized vector pointing in the direction the entity is heading. 
  Vector2D    m_vHeading;

  //a vector perpendicular to the heading vector
  Vector2D    m_vSide; 

  double      m_dMass;
  
  //the maximum speed this entity may travel at.
  double      m_dMaxSpeed;

  //the maximum force this entity can produce to power itself 
  //(think rockets and thrust)
  double      m_dMaxForce;
  
  //the maximum rate (radians per second)this vehicle can rotate         
  double      m_dMaxTurnRate;

public:


  MovingEntity(Vector2D position,
               double   radius,
               Vector2D velocity,
               double   max_speed,
               Vector2D heading,
               double   mass,
               Vector2D scale,
               double   turn_rate,
               double   max_force):BaseGameEntity(BaseGameEntity::GetNextValidID()),
                                  m_vHeading(heading),
                                  m_vVelocity(velocity),
                                  m_dMass(mass),
                                  m_vSide(m_vHeading.Perp()),
                                  m_dMaxSpeed(max_speed),
                                  m_dMaxTurnRate(turn_rate),
                                  m_dMaxForce(max_force)
  {
    m_vPosition = position;
    m_dBoundingRadius = radius; 
    m_vScale = scale;
  }


  virtual ~MovingEntity(){}

  //accessors
  Vector2D  Velocity()const{return m_vVelocity;}
  void      SetVelocity(const Vector2D& NewVel){m_vVelocity = NewVel;}
  
  double    Mass()const{return m_dMass;}
  
  Vector2D  Side()const{return m_vSide;}

  double    MaxSpeed()const{return m_dMaxSpeed;}                       
  void      SetMaxSpeed(double new_speed){m_dMaxSpeed = new_speed;}
  
  double    MaxForce()const{return m_dMaxForce;}
  void      SetMaxForce(double mf){m_dMaxForce = mf;}

  bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq();}
  double    Speed()const{return m_vVelocity.Length();}
  double    SpeedSq()const{return m_vVelocity.LengthSq();}
  
  Vector2D  Heading()const{return m_vHeading;}
  void      SetHeading(Vector2D new_heading);
  bool      RotateHeadingToFacePosition(Vector2D target);

  double    MaxTurnRate()const{return m_dMaxTurnRate;}
  void      SetMaxTurnRate(double val){m_dMaxTurnRate = val;}

};


//--------------------------- RotateHeadingToFacePosition ---------------------
//
//  given a target position, this method rotates the entity's heading and
//  side vectors by an amount not greater than m_dMaxTurnRate until it
//  directly faces the target.
//
//  returns true when the heading is facing in the desired direction
//-----------------------------------------------------------------------------
inline bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
  Vector2D toTarget = Vec2DNormalize(target - m_vPosition);

  double dot = m_vHeading.Dot(toTarget);

  //some compilers lose acurracy so the value is clamped to ensure it
  //remains valid for the acos
  Clamp(dot, -1, 1);

  //first determine the angle between the heading vector and the target
  double angle = acos(dot);

  //return true if the player is facing the target
  if (angle < 0.00001) return true;

  //clamp the amount to turn to the max turn rate
  if (angle > m_dMaxTurnRate) angle = m_dMaxTurnRate;
  
  //The next few lines use a rotation matrix to rotate the player's heading
  //vector accordingly
	C2DMatrix RotationMatrix;
  
  //notice how the direction of rotation has to be determined when creating
  //the rotation matrix
	RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));	
  RotationMatrix.TransformVector2Ds(m_vHeading);
  RotationMatrix.TransformVector2Ds(m_vVelocity);

  //finally recreate m_vSide
  m_vSide = m_vHeading.Perp();

  return false;
}


//------------------------- SetHeading ----------------------------------------
//
//  first checks that the given heading is not a vector of zero length. If the
//  new heading is valid this fumction sets the entity's heading and side 
//  vectors accordingly
//-----------------------------------------------------------------------------
inline void MovingEntity::SetHeading(Vector2D new_heading)
{
  assert( (new_heading.LengthSq() - 1.0) < 0.00001);
  
  m_vHeading = new_heading;

  //the side vector must always be perpendicular to the heading
  m_vSide = m_vHeading.Perp();
}




#endif