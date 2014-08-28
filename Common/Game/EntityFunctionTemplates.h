#ifndef GAME_ENTITY_FUNCTION_TEMPLATES
#define GAME_ENTITY_FUNCTION_TEMPLATES

#include "game/BaseGameEntity.h"
#include "2d/geometry.h"



//////////////////////////////////////////////////////////////////////////
//
//  Some useful template functions
//
//////////////////////////////////////////////////////////////////////////

//------------------------- Overlapped -----------------------------------
//
//  tests to see if an entity is overlapping any of a number of entities
//  stored in a std container
//------------------------------------------------------------------------
template <class T, class conT>
bool Overlapped(const T* ob, const conT& conOb, double MinDistBetweenObstacles = 40.0)
{
  typename conT::const_iterator it;

  for (it=conOb.begin(); it != conOb.end(); ++it)
  {
    if (TwoCirclesOverlapped(ob->Pos(),
                             ob->BRadius()+MinDistBetweenObstacles,                             
                             (*it)->Pos(),
                             (*it)->BRadius()))
    {
      return true;
    }
  }

  return false;
}

//----------------------- TagNeighbors ----------------------------------
//
//  tags any entities contained in a std container that are within the
//  radius of the single entity parameter
//------------------------------------------------------------------------
template <class T, class conT>
void TagNeighbors(T* entity, conT& others, const double radius)
{
  typename conT::iterator it;

  //iterate through all entities checking for range
  for (it=others.begin(); it != others.end(); ++it)
  {
    //first clear any current tag
    (*it)->UnTag();

    //work in distance squared to avoid sqrts
    Vector2D to = (*it)->Pos() - entity->Pos();

    //the bounding radius of the other is taken into account by adding it 
    //to the range
    double range = radius + (*it)->BRadius();

    //if entity within range, tag for further consideration
    if ( ((*it) != entity) && (to.LengthSq() < range*range))
    {
      (*it)->Tag();
    }
    
  }//next entity
}


//------------------- EnforceNonPenetrationContraint ---------------------
//
//  Given a pointer to an entity and a std container of pointers to nearby
//  entities, this function checks to see if there is an overlap between
//  entities. If there is, then the entities are moved away from each
//  other
//------------------------------------------------------------------------
template <class T, class conT>
void EnforceNonPenetrationContraint(T entity, const conT& others)
{
  typename conT::const_iterator it;

  //iterate through all entities checking for any overlap of bounding
  //radii
  for (it=others.begin(); it != others.end(); ++it)
  {
    //make sure we don't check against this entity
    if (*it == entity) continue;

    //calculate the distance between the positions of the entities
    Vector2D ToEntity = entity->Pos() - (*it)->Pos();

    double DistFromEachOther = ToEntity.Length();

    //if this distance is smaller than the sum of their radii then this
    //entity must be moved away in the direction parallel to the
    //ToEntity vector   
    double AmountOfOverLap = (*it)->BRadius() + entity->BRadius() -
                             DistFromEachOther;

    if (AmountOfOverLap >= 0)
    {
      //move the entity a distance away equivalent to the amount of overlap.
      entity->SetPos(entity->Pos() + (ToEntity/DistFromEachOther) *
                     AmountOfOverLap);
    }
  }//next entity
}










#endif