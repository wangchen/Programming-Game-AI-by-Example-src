#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   RocketLauncher
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to implement a rocket launcher
//-----------------------------------------------------------------------------
#include "Raven_Weapon.h"



class  Raven_Bot;

class RocketLauncher : public Raven_Weapon
{
private:

  void     InitializeFuzzyModule();

public:

  RocketLauncher(Raven_Bot* owner);


  void Render();

  void ShootAt(Vector2D pos);

  double GetDesirability(double DistToTarget);
};



#endif