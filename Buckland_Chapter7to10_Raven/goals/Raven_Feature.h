#ifndef RAVEN_FEATURE_H
#define RAVEN_FEATURE_H
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Feature.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   class that implements methods to extract feature specific
//          information from the Raven game world and present it as 
//          a value in the range 0 to 1
//
//-----------------------------------------------------------------------------
class Raven_Bot;

class Raven_Feature
{
public:

  //returns a value between 0 and 1 based on the bot's health. The better
  //the health, the higher the rating
  static double Health(Raven_Bot* pBot);
  
  //returns a value between 0 and 1 based on the bot's closeness to the 
  //given item. the further the item, the higher the rating. If there is no
  //item of the given type present in the game world at the time this method
  //is called the value returned is 1
  static double DistanceToItem(Raven_Bot* pBot, int ItemType);
  
  //returns a value between 0 and 1 based on how much ammo the bot has for
  //the given weapon, and the maximum amount of ammo the bot can carry. The
  //closer the amount carried is to the max amount, the higher the score
  static double IndividualWeaponStrength(Raven_Bot* pBot, int WeaponType);

  //returns a value between 0 and 1 based on the total amount of ammo the
  //bot is carrying each of the weapons. Each of the three weapons a bot can
  //pick up can contribute a third to the score. In other words, if a bot
  //is carrying a RL and a RG and has max ammo for the RG but only half max
  //for the RL the rating will be 1/3 + 1/6 + 0 = 0.5
  static double TotalWeaponStrength(Raven_Bot* pBot);
};



#endif