#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H
//-----------------------------------------------------------------------------
//
//  Name:    TriggerSystem.h
//
//  Author:  Mat Buckland (ai-junkie.com)
//
//  Desc:    Class to manage a collection of triggers. Triggers may be
//           registered with an instance of this class. The instance then 
//           takes care of updating those triggers and of removing them from
//           the system if their lifetime has expired.
//
//-----------------------------------------------------------------------------
template <class trigger_type>
class TriggerSystem
{
public:

  typedef std::list<trigger_type*> TriggerList;

private:

  TriggerList   m_Triggers; 


  //this method iterates through all the triggers present in the system and
  //calls their Update method in order that their internal state can be
  //updated if necessary. It also removes any triggers from the system that
  //have their m_bRemoveFromGame field set to true.
  void UpdateTriggers()
  {
    TriggerList::iterator curTrg = m_Triggers.begin();
    while (curTrg != m_Triggers.end())
    {
      //remove trigger if dead
      if ((*curTrg)->isToBeRemoved())
      {
        delete *curTrg;

        curTrg = m_Triggers.erase(curTrg);
      }
      else
      {
        //update this trigger
        (*curTrg)->Update();

        ++curTrg;
      }
    }
  }

  //this method iterates through the container of entities passed as a
  //parameter and passes each one to the Try method of each trigger *provided*
  //the entity is alive and provided the entity is ready for a trigger update.
  template <class ContainerOfEntities>
  void TryTriggers(ContainerOfEntities& entities)
  {
    //test each entity against the triggers
    ContainerOfEntities::iterator curEnt = entities.begin();
    for (curEnt; curEnt != entities.end(); ++curEnt)
    {
      //an entity must be ready for its next trigger update and it must be 
      //alive before it is tested against each trigger.
      if ((*curEnt)->isReadyForTriggerUpdate() && (*curEnt)->isAlive())
      {
        TriggerList::const_iterator curTrg;
        for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
        {
          (*curTrg)->Try(*curEnt);
        }
      }
    }
  }
  

public:

  ~TriggerSystem()
  {
    Clear();
  }

  //this deletes any current triggers and empties the trigger list
  void Clear()
  {
    TriggerList::iterator curTrg;
    for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
    {
      delete *curTrg;
    }

    m_Triggers.clear();
  }

  //This method should be called each update-step of the game. It will first
  //update the internal state odf the triggers and then try each entity against
  //each active trigger to test if any should be triggered.
  template <class ContainerOfEntities>
  void Update(ContainerOfEntities& entities)
  {
    UpdateTriggers();
    TryTriggers(entities);
  }

  //this is used to register triggers with the TriggerSystem (the TriggerSystem
  //will take care of tidying up memory used by a trigger)
  void Register(trigger_type* trigger)
  {
    m_Triggers.push_back(trigger);
  }

  //some triggers are required to be rendered (like giver-triggers for example)
  void Render()
  {
    TriggerList::iterator curTrg;
    for (curTrg = m_Triggers.begin(); curTrg != m_Triggers.end(); ++curTrg)
    {
      (*curTrg)->Render();
    }
  }

  const TriggerList& GetTriggers()const{return m_Triggers;}

};


#endif