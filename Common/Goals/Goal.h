#ifndef GOAL_H
#define GOAL_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Base goal class.
//-----------------------------------------------------------------------------

struct Telegram;
#include "misc/cgdi.h"
#include "misc/TypeToString.h"



template <class entity_type>
class Goal
{
public:

   enum {active, inactive, completed, failed};
  
protected:

  //an enumerated type specifying the type of goal
  int             m_iType;

  //a pointer to the entity that owns this goal
  entity_type*    m_pOwner;

  //an enumerated value indicating the goal's status (active, inactive,
  //completed, failed)
  int             m_iStatus;


  /* the following methods were created to factor out some of the commonality
     in the implementations of the Process method() */

  //if m_iStatus = inactive this method sets it to active and calls Activate()
  void ActivateIfInactive();

  //if m_iStatus is failed this method sets it to inactive so that the goal
  //will be reactivated (and therefore re-planned) on the next update-step.
  void ReactivateIfFailed();

public:

  //note how goals start off in the inactive state
  Goal(entity_type*  pE, int type):m_iType(type),
                                   m_pOwner(pE),
                                   m_iStatus(inactive)
  {}

  virtual ~Goal(){}

  //logic to run when the goal is activated.
  virtual void Activate() = 0;

  //logic to run each update-step
  virtual int  Process() = 0;

  //logic to run when the goal is satisfied. (typically used to switch
  //off any active steering behaviors)
  virtual void Terminate() = 0;

  //goals can handle messages. Many don't though, so this defines a default
  //behavior
  virtual bool HandleMessage(const Telegram& msg){return false;}


  //a Goal is atomic and cannot aggregate subgoals yet we must implement
  //this method to provide the uniform interface required for the goal
  //hierarchy.
  virtual void AddSubgoal(Goal<entity_type>* g)
  {throw std::runtime_error("Cannot add goals to atomic goals");}


  bool         isComplete()const{return m_iStatus == completed;} 
  bool         isActive()const{return m_iStatus == active;}
  bool         isInactive()const{return m_iStatus == inactive;}
  bool         hasFailed()const{return m_iStatus == failed;}
  int          GetType()const{return m_iType;}

  
  
  //this is used to draw the name of the goal at the specific position
  //used for debugging
  virtual void RenderAtPos(Vector2D& pos, TypeToString* tts)const;
  
  //used to render any goal specific information
  virtual void Render(){}
  
};




//if m_iStatus is failed this method sets it to inactive so that the goal
//will be reactivated (replanned) on the next update-step.
template <class entity_type>
void  Goal<entity_type>::ReactivateIfFailed()
{
  if (hasFailed())
  {
     m_iStatus = inactive;
  }
}

  
template <class entity_type>
void  Goal<entity_type>::ActivateIfInactive()
{
  if (isInactive())
  {
    Activate();   
  }
}

template <class entity_type>
void  Goal<entity_type>::RenderAtPos(Vector2D& pos, TypeToString* tts)const
{
  pos.y += 15;
  gdi->TransparentText();
  if (isComplete()) gdi->TextColor(0,255,0);
  if (isInactive()) gdi->TextColor(0,0,0);
  if (hasFailed()) gdi->TextColor(255,0,0);
  if (isActive()) gdi->TextColor(0,0,255);

  gdi->TextAtPos(pos.x, pos.y, tts->Convert(GetType())); 
}

#endif