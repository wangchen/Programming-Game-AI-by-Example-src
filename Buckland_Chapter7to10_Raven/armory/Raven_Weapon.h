#ifndef WEAPON_BASE_H
#define WEAPON_BASE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Weapon.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Base Weapon class for the raven project
//-----------------------------------------------------------------------------
#include <vector>

#include "2d/Vector2D.h"
#include "time/CrudeTimer.h"
#include "misc/utils.h"
#include "../lua/Raven_Scriptor.h"
#include "../Raven_Bot.h"
#include "Fuzzy/FuzzyModule.h"



class  Raven_Bot;

class Raven_Weapon
{
protected:

  //a weapon is always (in this game) carried by a bot
  Raven_Bot*    m_pOwner;

  //an enumeration indicating the type of weapon
  unsigned int  m_iType;

  //fuzzy logic is used to determine the desirability of a weapon. Each weapon
  //owns its own instance of a fuzzy module because each has a different rule 
  //set for inferring desirability.
  FuzzyModule   m_FuzzyModule;

  //amount of ammo carried for this weapon
  unsigned int  m_iNumRoundsLeft;

  //maximum number of rounds a bot can carry for this weapon
  unsigned int  m_iMaxRoundsCarried;
  
  //the number of times this weapon can be fired per second
  double         m_dRateOfFire;

  //the earliest time the next shot can be taken
  double         m_dTimeNextAvailable;

  //this is used to keep a local copy of the previous desirability score
  //so that we can give some feedback for debugging
  double         m_dLastDesirabilityScore;

  //this is the prefered distance from the enemy when using this weapon
  double         m_dIdealRange;

  //the max speed of the projectile this weapon fires
  double         m_dMaxProjectileSpeed;

  //The number of times a weapon can be discharges depends on its rate of fire.
  //This method returns true if the weapon is able to be discharged at the 
  //current time. (called from ShootAt() )
  bool          isReadyForNextShot();

  //this is called when a shot is fired to update m_dTimeNextAvailable
  void          UpdateTimeWeaponIsNextAvailable();

  //this method initializes the fuzzy module with the appropriate fuzzy 
  //variables and rule base.
  virtual void  InitializeFuzzyModule() = 0;

  //vertex buffers containing the weapon's geometry
  std::vector<Vector2D>   m_vecWeaponVB;
  std::vector<Vector2D>   m_vecWeaponVBTrans;



public:

  Raven_Weapon(unsigned int TypeOfGun,
               unsigned int DefaultNumRounds,
               unsigned int MaxRoundsCarried,
               double        RateOfFire,
               double        IdealRange,
               double        ProjectileSpeed,
               Raven_Bot*   OwnerOfGun):m_iType(TypeOfGun),
                                 m_iNumRoundsLeft(DefaultNumRounds),
                                 m_pOwner(OwnerOfGun),
                                 m_dRateOfFire(RateOfFire),
                                 m_iMaxRoundsCarried(MaxRoundsCarried),
                                 m_dLastDesirabilityScore(0),
                                 m_dIdealRange(IdealRange),
                                 m_dMaxProjectileSpeed(ProjectileSpeed)
  {  
    m_dTimeNextAvailable = Clock->GetCurrentTime();
  }

  virtual ~Raven_Weapon(){}

  //this method aims the weapon at the given target by rotating the weapon's
  //owner's facing direction (constrained by the bot's turning rate). It returns  
  //true if the weapon is directly facing the target.
  bool          AimAt(Vector2D target)const;

  //this discharges a projectile from the weapon at the given target position
  //(provided the weapon is ready to be discharged... every weapon has its
  //own rate of fire)
  virtual void  ShootAt(Vector2D pos) = 0;

  //each weapon has its own shape and color
  virtual void  Render() = 0;

  //this method returns a value representing the desirability of using the
  //weapon. This is used by the AI to select the most suitable weapon for
  //a bot's current situation. This value is calculated using fuzzy logic
  virtual double GetDesirability(double DistToTarget)=0;

  //returns the desirability score calculated in the last call to GetDesirability
  //(just used for debugging)
  double         GetLastDesirabilityScore()const{return m_dLastDesirabilityScore;}

  //returns the maximum speed of the projectile this weapon fires
  double         GetMaxProjectileSpeed()const{return m_dMaxProjectileSpeed;}

  //returns the number of rounds remaining for the weapon
  int           NumRoundsRemaining()const{return m_iNumRoundsLeft;}
  void          DecrementNumRounds(){if (m_iNumRoundsLeft>0) --m_iNumRoundsLeft;}
  void          IncrementRounds(int num); 
  unsigned int  GetType()const{return m_iType;}
  double         GetIdealRange()const{return m_dIdealRange;}
};


///////////////////////////////////////////////////////////////////////////////
//------------------------ ReadyForNextShot -----------------------------------
//
//  returns true if the weapon is ready to be discharged
//-----------------------------------------------------------------------------
inline bool Raven_Weapon::isReadyForNextShot()
{
  if (Clock->GetCurrentTime() > m_dTimeNextAvailable)
  {
    return true;
  }

  return false;
}

//-----------------------------------------------------------------------------
inline void Raven_Weapon::UpdateTimeWeaponIsNextAvailable()
{
  m_dTimeNextAvailable = Clock->GetCurrentTime() + 1.0/m_dRateOfFire;
}


//-----------------------------------------------------------------------------
inline bool Raven_Weapon::AimAt(Vector2D target)const
{
  return m_pOwner->RotateFacingTowardPosition(target);
}

//-----------------------------------------------------------------------------
inline void Raven_Weapon::IncrementRounds(int num)
{
  m_iNumRoundsLeft+=num;
  Clamp(m_iNumRoundsLeft, 0, m_iMaxRoundsCarried);
} 





#endif