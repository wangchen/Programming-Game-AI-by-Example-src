#ifndef GOAL_NEGOTIATE_DOOR_H
#define GOAL_NEGOTIATE_DOOR_H
#pragma warning(disable : 4786)

#include "../Raven_Bot.h"
#include "../navigation/PathEdge.h"
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"

class Goal_NegotiateDoor : public Goal_Composite<Raven_Bot>
{
private:
  PathEdge m_PathEdge;

  bool m_bLastEdgeInPath;

public:
  Goal_NegotiateDoor(Raven_Bot * pBot, PathEdge edge, bool LastEdge);

  //the usual suspects
  void Activate();
  int Process();
  void Terminate() {}
};

#endif
