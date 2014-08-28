#ifndef GOAL_COMPOSITE_H
#define GOAL_COMPOSITE_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Composite.h      
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Base composite goal class
//-----------------------------------------------------------------------------
#include <list>
#include "Goal.h"


template <class entity_type>
class Goal_Composite : public Goal<entity_type>
{
private:

    typedef std::list<Goal<entity_type>* > SubgoalList;

protected:

  //composite goals may have any number of subgoals
  SubgoalList   m_SubGoals;


  //processes any subgoals that may be present
  int  ProcessSubgoals();

  //passes the message to the front-most subgoal
  bool ForwardMessageToFrontMostSubgoal(const Telegram& msg);


public:

  Goal_Composite(entity_type* pE, int type):Goal<entity_type>(pE,type){}

  //when this object is destroyed make sure any subgoals are terminated
  //and destroyed.
  virtual ~Goal_Composite(){RemoveAllSubgoals();}

  //logic to run when the goal is activated.
  virtual void Activate() = 0;

  //logic to run each update-step.
  virtual int  Process() = 0;

  //logic to run prior to the goal's destruction
  virtual void Terminate() = 0;

  //if a child class of Goal_Composite does not define a message handler
  //the default behavior is to forward the message to the front-most
  //subgoal
  virtual bool HandleMessage(const Telegram& msg)
  { return ForwardMessageToFrontMostSubgoal(msg);}

  //adds a subgoal to the front of the subgoal list
  void         AddSubgoal(Goal<entity_type>* g);

  //this method iterates through the subgoals and calls each one's Terminate
  //method before deleting the subgoal and removing it from the subgoal list
  void         RemoveAllSubgoals();


  virtual void RenderAtPos(Vector2D& pos, TypeToString* tts)const;
  //this is only used to render information for debugging purposes
  virtual void Render();
};





//---------------------- RemoveAllSubgoals ------------------------------------
//-----------------------------------------------------------------------------
template <class entity_type>
void Goal_Composite<entity_type>::RemoveAllSubgoals()
{
  for (SubgoalList::iterator it = m_SubGoals.begin();
       it != m_SubGoals.end();
       ++it)
  {  
    (*it)->Terminate();
    
    delete *it;
  }

  m_SubGoals.clear();
}
 

//-------------------------- ProcessSubGoals ----------------------------------
//
//  this method first removes any completed goals from the front of the
//  subgoal list. It then processes the next goal in the list (if there is one)
//-----------------------------------------------------------------------------
template <class entity_type>
int Goal_Composite<entity_type>::ProcessSubgoals()
{ 
  //remove all completed and failed goals from the front of the subgoal list
  while (!m_SubGoals.empty() &&
         (m_SubGoals.front()->isComplete() || m_SubGoals.front()->hasFailed()))
  {    
    m_SubGoals.front()->Terminate();
    delete m_SubGoals.front(); 
    m_SubGoals.pop_front();
  }

  //if any subgoals remain, process the one at the front of the list
  if (!m_SubGoals.empty())
  { 
    //grab the status of the front-most subgoal
    int StatusOfSubGoals = m_SubGoals.front()->Process();

    //we have to test for the special case where the front-most subgoal
    //reports 'completed' *and* the subgoal list contains additional goals.When
    //this is the case, to ensure the parent keeps processing its subgoal list
    //we must return the 'active' status.
    if (StatusOfSubGoals == completed && m_SubGoals.size() > 1)
    {
      return active;
    }

    return StatusOfSubGoals;
  }
  
  //no more subgoals to process - return 'completed'
  else
  {
    return completed;
  }
}

//----------------------------- AddSubgoal ------------------------------------
template <class entity_type>
void Goal_Composite<entity_type>::AddSubgoal(Goal<entity_type>* g)
{   
  //add the new goal to the front of the list
  m_SubGoals.push_front(g);
}



//---------------- ForwardMessageToFrontMostSubgoal ---------------------------
//
//  passes the message to the goal at the front of the queue
//-----------------------------------------------------------------------------
template <class entity_type>
bool Goal_Composite<entity_type>::ForwardMessageToFrontMostSubgoal(const Telegram& msg)
{
  if (!m_SubGoals.empty())
  {
    return m_SubGoals.front()->HandleMessage(msg);
  }

  //return false if the message has not been handled
  return false;
}


//-------------------------- RenderAtPos --------------------------------------
template <class entity_type>
void  Goal_Composite<entity_type>::RenderAtPos(Vector2D& pos, TypeToString* tts)const
{
  Goal<entity_type>::RenderAtPos(pos, tts);

  pos.x += 10;

  gdi->TransparentText();
  SubgoalList::const_reverse_iterator it;
  for (it=m_SubGoals.rbegin(); it != m_SubGoals.rend(); ++it)
  {
    (*it)->RenderAtPos(pos, tts);
  }

  pos.x -= 10;
}

template <class entity_type>
void  Goal_Composite<entity_type>::Render()
{
  if (!m_SubGoals.empty())
  {
    m_SubGoals.front()->Render();
  }
}



#endif

