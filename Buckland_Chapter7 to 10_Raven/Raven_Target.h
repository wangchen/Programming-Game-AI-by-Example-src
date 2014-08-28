#ifndef RAVEN_TARGET_H
#define RAVEN_TARGET_H
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Target
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   struct to hold data about a target
//
//-----------------------------------------------------------------------------

struct Raven_Target
{
    //the current target (this will be null if there is no target assigned)
  Raven_Bot*         Instance;

  //a vector marking the last visible position of the target.
  Vector2D           LastVisiblePosition;

  //true if target is within the field of view of the owner
  bool               isWithinFOV;

  //true if there is no obstruction between the target and the owner, 
  //permitting a shot. (for example, a the target may be behind the owner
  //but in the open. In this situation m_bWithinFOV is false but m_bShootable
  //is true). This value is utilized by the owner to determine whether or not
  //to turn around and face the target when approached from behind
  bool               isShootable;

  Raven_Target():Instance(0), isWithinFOV(false), isShootable(false){}

  void Reset(){Instance = 0; isWithinFOV = false; isShootable = false;}
};


#endif