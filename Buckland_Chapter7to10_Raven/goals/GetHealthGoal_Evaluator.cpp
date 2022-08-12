#include "GetHealthGoal_Evaluator.h"
#include "../Raven_ObjectEnumerations.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"


//---------------------- CalculateDesirability -------------------------------------
//-----------------------------------------------------------------------------
double GetHealthGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
  //first grab the distance to the closest instance of a health item
  double Distance = Raven_Feature::DistanceToItem(pBot, type_health);

  //if the distance feature is rated with a value of 1 it means that the
  //item is either not present on the map or too far away to be worth 
  //considering, therefore the desirability is zero
  if (Distance == 1)
  {
    return 0;
  }
  else
  {
    //value used to tweak the desirability
    const double Tweaker = 0.2;
  
    //the desirability of finding a health item is proportional to the amount
    //of health remaining and inversely proportional to the distance from the
    //nearest instance of a health item.
    double Desirability = Tweaker * (1-Raven_Feature::Health(pBot)) / 
                        (Raven_Feature::DistanceToItem(pBot, type_health));
 
    //ensure the value is in the range 0 to 1
    Clamp(Desirability, 0, 1);
  
    //bias the value according to the personality of the bot
    Desirability *= m_dCharacterBias;

    return Desirability;
  }
}



//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void GetHealthGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
  pBot->GetBrain()->AddGoal_GetItem(type_health); 
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void GetHealthGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
  gdi->TextAtPos(Position, "H: " + ttos(CalculateDesirability(pBot), 2));
  return;
  
  std::string s = ttos(1-Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::DistanceToItem(pBot, type_health));
  gdi->TextAtPos(Position+Vector2D(0,15), s);
}