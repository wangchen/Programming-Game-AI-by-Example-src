#include "Raven_Projectile.h"
#include "../Raven_Game.h"
#include <list>

//------------------ GetClosestIntersectingBot --------------------------------

Raven_Bot* Raven_Projectile::GetClosestIntersectingBot(Vector2D    From,
                                                       Vector2D    To)const
{
  Raven_Bot* ClosestIntersectingBot = 0;
  double ClosestSoFar = MaxDouble;

  //iterate through all entities checking against the line segment FromTo
  std::list<Raven_Bot*>::const_iterator curBot;
  for (curBot =  m_pWorld->GetAllBots().begin();
       curBot != m_pWorld->GetAllBots().end();
       ++curBot)
  {
    //make sure we don't check against the shooter of the projectile
    if ( ((*curBot)->ID() != m_iShooterID))
    {
      //if the distance to FromTo is less than the entity's bounding radius then
      //there is an intersection
      if (DistToLineSegment(From, To, (*curBot)->Pos()) < (*curBot)->BRadius())
      {
        //test to see if this is the closest so far
        double Dist = Vec2DDistanceSq((*curBot)->Pos(), m_vOrigin);

        if (Dist < ClosestSoFar)
        {
          Dist = ClosestSoFar;
          ClosestIntersectingBot = *curBot;
        }
      }
    }

  }

  return ClosestIntersectingBot;
}


//---------------------- GetListOfIntersectingBots ----------------------------
std::list<Raven_Bot*> Raven_Projectile::GetListOfIntersectingBots(Vector2D From,
                                                                  Vector2D To)const
{
  //this will hold any bots that are intersecting with the line segment
  std::list<Raven_Bot*> hits;

  //iterate through all entities checking against the line segment FromTo
  std::list<Raven_Bot*>::const_iterator curBot;
  for (curBot =  m_pWorld->GetAllBots().begin();
       curBot != m_pWorld->GetAllBots().end();
       ++curBot)
  {
    //make sure we don't check against the shooter of the projectile
    if ( ((*curBot)->ID() != m_iShooterID))
    {
      //if the distance to FromTo is less than the entities bounding radius then
      //there is an intersection so add it to hits
      if (DistToLineSegment(From, To, (*curBot)->Pos()) < (*curBot)->BRadius())
      {
        hits.push_back(*curBot);
      }
    }

  }

  return hits;
}

