#ifndef MINERSWIFE_H
#define MINERSWIFE_H

#include <string>

#include "State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinersWifeOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "StateMachine.h"
#include "misc/Utils.h"



class MinersWife : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<MinersWife>*  m_pStateMachine;

  location_type              m_Location;


public:

  MinersWife(int id):BaseGameEntity(id),
                     m_Location(shack)
                                                                      
  {
    m_pStateMachine = new StateMachine<MinersWife>(this);

    m_pStateMachine->SetCurrentState(DoHouseWork::Instance());

    m_pStateMachine->SetGlobalState(WifesGlobalState::Instance());
  }

  ~MinersWife(){delete m_pStateMachine;}


  void Update();

  StateMachine<MinersWife>*  GetFSM()const{return m_pStateMachine;}

  //----------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(const location_type loc){m_Location=loc;}
   
};



#endif
