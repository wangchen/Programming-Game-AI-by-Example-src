#ifndef GOAL_TRAVERSE_EDGE_H
#define GOAL_TRAVERSE_EDGE_H
#pragma warning(disable : 4786)

#include "../navigation/PathEdge.h"
#include "../navigation/Raven_PathPlanner.h"
#include "2d/Vector2D.h"
#include "Goals/Goal.h"

class Goal_TraverseEdge : public Goal<Raven_Bot>
{
private:
  //the edge the bot will follow
  PathEdge m_Edge;

  //true if m_Edge is the last in the path.
  bool m_bLastEdgeInPath;

  //the estimated time the bot should take to traverse the edge
  double m_dTimeExpected;

  //this records the time this goal was activated
  double m_dStartTime;

  //returns true if the bot gets stuck
  bool isStuck() const;

public:
  Goal_TraverseEdge(Raven_Bot * pBot, PathEdge edge, bool LastEdge);

  //the usual suspects
  void Activate();
  int Process();
  void Terminate();
  void Render();
};

#endif
