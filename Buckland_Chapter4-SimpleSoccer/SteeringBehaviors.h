#ifndef SteeringBehaviorsS_H
#define SteeringBehaviorsS_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   SteeringBehaviorss.h
//
//  Desc:   class to encapsulate steering behaviors for a soccer player
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>
#include <windows.h>
#include <string>


#include "2D/Vector2D.h"

class PlayerBase;
class SoccerPitch;
class SoccerBall;
class CWall;
class CObstacle;


//---------------------------- class details -----------------------------

class SteeringBehaviors
{
private:
  
  PlayerBase*   m_pPlayer;                                                  

  SoccerBall*   m_pBall;

  //the steering force created by the combined effect of all
  //the selected behaviors
  Vector2D     m_vSteeringForce;

  //the current target (usually the ball or predicted ball position)
  Vector2D     m_vTarget;

  //the distance the player tries to interpose from the target
  double        m_dInterposeDist;

  //multipliers. 
  double        m_dMultSeparation;

  //how far it can 'see'
  double        m_dViewDistance;


  //binary flags to indicate whether or not a behavior should be active
  int           m_iFlags;

  enum behavior_type
  {
    none               = 0x0000,
    seek               = 0x0001,
    arrive             = 0x0002,
    separation         = 0x0004,
    pursuit            = 0x0008,
    interpose          = 0x0010
  };

  //used by group behaviors to tag neighbours
  bool         m_bTagged;
  
  //Arrive makes use of these to determine how quickly a vehicle
  //should decelerate to its target
  enum Deceleration{slow = 3, normal = 2, fast = 1};


  //this behavior moves the agent towards a target position
  Vector2D Seek(Vector2D target);

  //this behavior is similar to seek but it attempts to arrive 
  //at the target with a zero velocity
  Vector2D Arrive(Vector2D target, Deceleration decel);

  //This behavior predicts where its prey will be and seeks
  //to that location
  Vector2D Pursuit(const SoccerBall* ball);
 
  Vector2D Separation();

  //this attempts to steer the agent to a position between the opponent
  //and the object
  Vector2D Interpose(const SoccerBall* ball,
                     Vector2D pos,
                     double    DistFromTarget);


  //finds any neighbours within the view radius
  void      FindNeighbours();


  //this function tests if a specific bit of m_iFlags is set
  bool      On(behavior_type bt){return (m_iFlags & bt) == bt;}

  bool      AccumulateForce(Vector2D &sf, Vector2D ForceToAdd);

  Vector2D  SumForces();

  //a vertex buffer to contain the feelers rqd for dribbling
  std::vector<Vector2D> m_Antenna;

  
public:

  SteeringBehaviors(PlayerBase*       agent,
                    SoccerPitch*  world,
                    SoccerBall*   ball);

  virtual ~SteeringBehaviors(){}

 
  Vector2D Calculate();

  //calculates the component of the steering force that is parallel
  //with the vehicle heading
  double    ForwardComponent();

  //calculates the component of the steering force that is perpendicuar
  //with the vehicle heading
  double    SideComponent();

  Vector2D Force()const{return m_vSteeringForce;}

  //renders visual aids and info for seeing how each behavior is
  //calculated
  void      RenderInfo();
  void      RenderAids();

  Vector2D  Target()const{return m_vTarget;}
  void      SetTarget(const Vector2D t){m_vTarget = t;}

  double     InterposeDistance()const{return m_dInterposeDist;}
  void      SetInterposeDistance(double d){m_dInterposeDist = d;}

  bool      Tagged()const{return m_bTagged;}
  void      Tag(){m_bTagged = true;}
  void      UnTag(){m_bTagged = false;}
  

  void SeekOn(){m_iFlags |= seek;}
  void ArriveOn(){m_iFlags |= arrive;}
  void PursuitOn(){m_iFlags |= pursuit;}
  void SeparationOn(){m_iFlags |= separation;}
  void InterposeOn(double d){m_iFlags |= interpose; m_dInterposeDist = d;}

  
  void SeekOff()  {if(On(seek))   m_iFlags ^=seek;}
  void ArriveOff(){if(On(arrive)) m_iFlags ^=arrive;}
  void PursuitOff(){if(On(pursuit)) m_iFlags ^=pursuit;}
  void SeparationOff(){if(On(separation)) m_iFlags ^=separation;}
  void InterposeOff(){if(On(interpose)) m_iFlags ^=interpose;}


  bool SeekIsOn(){return On(seek);}
  bool ArriveIsOn(){return On(arrive);}
  bool PursuitIsOn(){return On(pursuit);}
  bool SeparationIsOn(){return On(separation);}
  bool InterposeIsOn(){return On(interpose);}

};




#endif