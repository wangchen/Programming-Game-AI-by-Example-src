#ifndef PELLET_H
#define PELLET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Pellet.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   class to implement a pellet type projectile
//
//-----------------------------------------------------------------------------

#include "Raven_Projectile.h"

class Raven_Bot;
class Raven_Environment;

class Pellet : public Raven_Projectile
{
private:

  //when this projectile hits something it's trajectory is rendered
  //for this amount of time
  double   m_dTimeShotIsVisible;

  //tests the trajectory of the pellet for an impact
  void  TestForImpact();

  //returns true if the shot is still to be rendered
  bool  isVisibleToPlayer()const{return Clock->GetCurrentTime() < m_dTimeOfCreation + m_dTimeShotIsVisible;}
  
public:

  Pellet(Raven_Bot* shooter, Vector2D target);
  
  void Render();

  void Update();
  
};


#endif