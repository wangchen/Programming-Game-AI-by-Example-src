#ifndef RAVEN_WEAPONSYSTEM
#define RAVEN_WEAPONSYSTEM
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_WeaponSystem.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   class to manage all operations specific to weapons and their
//          deployment
//
//-----------------------------------------------------------------------------
#include <map>
#include "2d/vector2d.h"

class Raven_Bot;
class Raven_Weapon;



class Raven_WeaponSystem
{
private:
  
  //a map of weapon instances indexed into by type
  typedef std::map<int, Raven_Weapon*>  WeaponMap;

private:

  Raven_Bot*       m_pOwner;

  //pointers to the weapons the bot is carrying (a bot may only carry one
  //instance of each weapon)
  WeaponMap        m_WeaponMap;

  //a pointer to the weapon the bot is currently holding
  Raven_Weapon*    m_pCurrentWeapon;

  //this is the minimum amount of time a bot needs to see an opponent before
  //it can react to it. This variable is used to prevent a bot shooting at
  //an opponent the instant it becomes visible.
  double            m_dReactionTime;

  //each time the current weapon is fired a certain amount of random noise is
  //added to the the angle of the shot. This prevents the bots from hitting
  //their opponents 100% of the time. The lower this value the more accurate
  //a bot's aim will be. Recommended values are between 0 and 0.2 (the value
  //represents the max deviation in radians that can be added to each shot).
  double            m_dAimAccuracy;

  //the amount of time a bot will continue aiming at the position of the target
  //even if the target disappears from view.
  double            m_dAimPersistance;

  //predicts where the target will be by the time it takes the current weapon's
  //projectile type to reach it. Used by TakeAimAndShoot
  Vector2D    PredictFuturePositionOfTarget()const;

  //adds a random deviation to the firing angle not greater than m_dAimAccuracy 
  //rads
  void        AddNoiseToAim(Vector2D& AimingPos)const;

public:

  Raven_WeaponSystem(Raven_Bot* owner,
                     double      ReactionTime,
                     double      AimAccuracy,
                     double      AimPersistance);
  
  ~Raven_WeaponSystem();

  //sets up the weapon map with just one weapon: the blaster
  void          Initialize();

  //this method aims the bot's current weapon at the target (if there is a
  //target) and, if aimed correctly, fires a round. (Called each update-step
  //from Raven_Bot::Update)
  void          TakeAimAndShoot()const;

  //this method determines the most appropriate weapon to use given the current
  //game state. (Called every n update-steps from Raven_Bot::Update)
  void          SelectWeapon();
  
  //this will add a weapon of the specified type to the bot's inventory. 
  //If the bot already has a weapon of this type only the ammo is added. 
  //(called by the weapon giver-triggers to give a bot a weapon)
  void          AddWeapon(unsigned int weapon_type);

  //changes the current weapon to one of the specified type (provided that type
  //is in the bot's possession)
  void          ChangeWeapon(unsigned int type);

  //shoots the current weapon at the given position
  void          ShootAt(Vector2D pos)const;

  //returns a pointer to the current weapon
  Raven_Weapon* GetCurrentWeapon()const{return m_pCurrentWeapon;} 

  //returns a pointer to the specified weapon type (if in inventory, null if 
  //not)
  Raven_Weapon* GetWeaponFromInventory(int weapon_type);

  //returns the amount of ammo remaining for the specified weapon
  int           GetAmmoRemainingForWeapon(unsigned int weapon_type);

  double         ReactionTime()const{return m_dReactionTime;}

  void          RenderCurrentWeapon()const;
  void          RenderDesirabilities()const;
};

#endif