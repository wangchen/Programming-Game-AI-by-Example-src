#ifndef TEAMSTATES_H
#define TEAMSTATES_H
//------------------------------------------------------------------------
//
//  Name: TeamStates.h
//
//  Desc: State prototypes for soccer team states
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>

#include "FSM/State.h"
#include "Messaging/Telegram.h"


class SoccerTeam;





//------------------------------------------------------------------------
class Attacking : public State<SoccerTeam>
{ 
private:
  
  Attacking(){}

public:

  //this is a singleton
  static Attacking* Instance();

  void Enter(SoccerTeam* team);

  void Execute(SoccerTeam* team);

  void Exit(SoccerTeam* team);

  bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class Defending : public State<SoccerTeam>
{ 
private:
  
  Defending(){}

public:

    //this is a singleton
  static Defending* Instance();

  void Enter(SoccerTeam* team);

  void Execute(SoccerTeam* team);

  void Exit(SoccerTeam* team);

  bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class PrepareForKickOff : public State<SoccerTeam>
{ 
private:
  
  PrepareForKickOff(){}

public:

    //this is a singleton
  static PrepareForKickOff* Instance();
  
  void Enter(SoccerTeam* team);

  void Execute(SoccerTeam* team);

  void Exit(SoccerTeam* team);

  bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};


#endif