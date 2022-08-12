#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Projectile.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Base class to define a projectile type. A projectile of the correct
//          type is created whnever a weapon is fired. In Raven there are four
//          types of projectile: Slugs (railgun), Pellets (shotgun), Rockets
//          (rocket launcher ) and Bolts (Blaster) 
//-----------------------------------------------------------------------------
#include "game/MovingEntity.h"
#include "2d/Vector2D.h"
#include "time/CrudeTimer.h"
#include <list>

class Raven_Game;
class Raven_Bot;


class Raven_Projectile : public MovingEntity
{
protected:

  //the ID of the entity that fired this
  int           m_iShooterID;

  //the place the projectile is aimed at
  Vector2D      m_vTarget;

  //a pointer to the world data
  Raven_Game*   m_pWorld;

  //where the projectile was fired from
  Vector2D      m_vOrigin;

  //how much damage the projectile inflicts
  int           m_iDamageInflicted;

  //is it dead? A dead projectile is one that has come to the end of its
  //trajectory and cycled through any explosion sequence. A dead projectile
  //can be removed from the world environment and deleted.
  bool          m_bDead;

  //this is set to true as soon as a projectile hits something
  bool          m_bImpacted;

  //the position where this projectile impacts an object
  Vector2D      m_vImpactPoint;

  //this is stamped with the time this projectile was instantiated. This is
  //to enable the shot to be rendered for a specific length of time
  double       m_dTimeOfCreation;

  Raven_Bot*            GetClosestIntersectingBot(Vector2D From,
                                                  Vector2D To)const;

  std::list<Raven_Bot*> GetListOfIntersectingBots(Vector2D From,
                                                  Vector2D To)const;


public:

  Raven_Projectile(Vector2D  target,   //the target's position
                   Raven_Game* world,  //a pointer to the world data
                   int      ShooterID, //the ID of the bot that fired this shot
                   Vector2D origin,  //the start position of the projectile
                   Vector2D heading,   //the heading of the projectile
                   int      damage,    //how much damage it inflicts
                   double    scale,    
                   double    MaxSpeed, 
                   double    mass,
                   double    MaxForce):  MovingEntity(origin,
                                                     scale,
                                                     Vector2D(0,0),
                                                     MaxSpeed,
                                                     heading,
                                                     mass,
                                                     Vector2D(scale, scale),
                                                     0, //max turn rate irrelevant here, all shots go straight
                                                     MaxForce),

                                        m_vTarget(target),
                                        m_bDead(false),
                                        m_bImpacted(false),
                                        m_pWorld(world),
                                        m_iDamageInflicted(damage),
                                        m_vOrigin(origin),
                                        m_iShooterID(ShooterID)
                

  {m_dTimeOfCreation = Clock->GetCurrentTime();}

  //unimportant for this class unless you want to implement a full state 
  //save/restore (which can be useful for debugging purposes)
  void Write(std::ostream&  os)const{}
  void Read (std::ifstream& is){}

  //must be implemented
  virtual void Update() = 0;
  virtual void Render() = 0;
  
  //set to true if the projectile has impacted and has finished any explosion 
  //sequence. When true the projectile will be removed from the game
  bool isDead()const{return m_bDead;}
  
  //true if the projectile has impacted but is not yet dead (because it
  //may be exploding outwards from the point of impact for example)
  bool HasImpacted()const{return m_bImpacted;}



};






#endif