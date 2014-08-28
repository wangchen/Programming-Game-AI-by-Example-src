#ifndef RAILGUN_H
#define RAILGUN_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Weapon_RailGun.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to implement a rail gun
//-----------------------------------------------------------------------------
#include "Raven_Weapon.h"


class  Raven_Bot;



class RailGun : public Raven_Weapon
{
private:

  void  InitializeFuzzyModule();

public:

  RailGun(Raven_Bot* owner);

  void  Render();

  void  ShootAt(Vector2D pos);

  double GetDesirability(double DistToTarget);
};



#endif