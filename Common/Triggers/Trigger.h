#ifndef TRIGGER_H
#define TRIGGER_H
//-----------------------------------------------------------------------------
//
//  Name:   Trigger.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   base class for a trigger. A trigger is an object that is
//          activated when an entity moves within its region of influence.
//
//-----------------------------------------------------------------------------
#include "game/BaseGameEntity.h"
#include "TriggerRegion.h"

struct Telegram;
struct Vector2D;

template <class entity_type>
class Trigger : public BaseGameEntity
{   
private:

  //Every trigger owns a trigger region. If an entity comes within this 
  //region the trigger is activated
  TriggerRegion* m_pRegionOfInfluence; 

  //if this is true the trigger will be removed from the game
  bool           m_bRemoveFromGame;

  //it's convenient to be able to deactivate certain types of triggers
  //on an event. Therefore a trigger can only be triggered when this
  //value is true (respawning triggers make good use of this facility)
  bool           m_bActive;

  //some types of trigger are twinned with a graph node. This enables
  //the pathfinding component of an AI to search a navgraph for a specific
  //type of trigger.
  int            m_iGraphNodeIndex;

protected:
  
  void SetGraphNodeIndex(int idx){m_iGraphNodeIndex = idx;}

  void SetToBeRemovedFromGame(){m_bRemoveFromGame = true;}
  void SetInactive(){m_bActive = false;}
  void SetActive(){m_bActive = true;}

  //returns true if the entity given by a position and bounding radius is
  //overlapping the trigger region
  bool isTouchingTrigger(Vector2D EntityPos, double EntityRadius)const;

  //child classes use one of these methods to initialize the trigger region
  void AddCircularTriggerRegion(Vector2D center, double radius);
  void AddRectangularTriggerRegion(Vector2D TopLeft, Vector2D BottomRight);

public:

  Trigger(unsigned int id):BaseGameEntity(id),
                           m_bRemoveFromGame(false),
                           m_bActive(true),
                           m_iGraphNodeIndex(-1),
                           m_pRegionOfInfluence(NULL)
                           
  {}

  virtual ~Trigger(){delete m_pRegionOfInfluence;}

  //when this is called the trigger determines if the entity is within the
  //trigger's region of influence. If it is then the trigger will be 
  //triggered and the appropriate action will be taken.
  virtual void  Try(entity_type*) = 0;

  //called each update-step of the game. This methods updates any internal
  //state the trigger may have
  virtual void  Update() = 0;

  int  GraphNodeIndex()const{return m_iGraphNodeIndex;}
  bool isToBeRemoved()const{return m_bRemoveFromGame;}
  bool isActive(){return m_bActive;}
};

 
//------------------------ AddCircularTriggerRegion ---------------------------
//-----------------------------------------------------------------------------
template <class entity_type>
void Trigger<entity_type>::AddCircularTriggerRegion(Vector2D center,
                                                    double    radius)
{
  //if this replaces an existing region, tidy up memory
  if (m_pRegionOfInfluence) delete m_pRegionOfInfluence;

  m_pRegionOfInfluence = new TriggerRegion_Circle(center, radius);
}

//--------------------- AddRectangularTriggerRegion ---------------------------
//-----------------------------------------------------------------------------
template <class entity_type>
void Trigger<entity_type>::AddRectangularTriggerRegion(Vector2D TopLeft,
                                                       Vector2D BottomRight)
{
  //if this replaces an existing region, tidy up memory
  if (m_pRegionOfInfluence) delete m_pRegionOfInfluence;

  m_pRegionOfInfluence = new TriggerRegion_Rectangle(TopLeft, BottomRight);
}

//--------------------- isTouchingTrigger -------------------------------------
//-----------------------------------------------------------------------------
template <class entity_type>
bool Trigger<entity_type>::isTouchingTrigger(Vector2D EntityPos,
                                             double    EntityRadius)const
{
  if (m_pRegionOfInfluence) 
  {
    return m_pRegionOfInfluence->isTouching(EntityPos, EntityRadius);
  }
    
  return false;
}


#endif