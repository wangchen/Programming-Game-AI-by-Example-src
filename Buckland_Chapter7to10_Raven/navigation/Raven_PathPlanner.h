#ifndef PATHPLANNER_H
#define PATHPLANNER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_PathPlanner.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to handle the creation of paths through a navigation graph
//-----------------------------------------------------------------------------
#include <list>
#include "TimeSlicedGraphAlgorithms.h"
#include "Graph/GraphAlgorithms.h"
#include "Graph/SparseGraph.h"
#include "PathEdge.h"
#include "../Raven_Map.h"

class Raven_Bot;


                                               
class Raven_PathPlanner
{
private:

  //for legibility
  enum {no_closest_node_found = -1};

public:

  //for ease of use typdef the graph edge/node types used by the navgraph
  typedef Raven_Map::NavGraph::EdgeType           EdgeType;
  typedef Raven_Map::NavGraph::NodeType           NodeType;
  typedef std::list<PathEdge>                     Path;
  
private:

  //A pointer to the owner of this class
  Raven_Bot*                          m_pOwner;

  //a reference to the navgraph
  const Raven_Map::NavGraph&          m_NavGraph;

  //a pointer to an instance of the current graph search algorithm.
  Graph_SearchTimeSliced<EdgeType>*  m_pCurrentSearch;
  
  //this is the position the bot wishes to plan a path to reach
  Vector2D                            m_vDestinationPos;


  //returns the index of the closest visible and unobstructed graph node to
  //the given position
  int   GetClosestNodeToPosition(Vector2D pos)const;

  //smooths a path by removing extraneous edges. (may not remove all
  //extraneous edges)
  void  SmoothPathEdgesQuick(Path& path);

  //smooths a path by removing extraneous edges. (removes *all* extraneous
  //edges)
  void  SmoothPathEdgesPrecise(Path& path);

  //called at the commencement of a new search request. It clears up the 
  //appropriate lists and memory in preparation for a new search request
  void  GetReadyForNewSearch();



public:

  ~Raven_PathPlanner();

  Raven_PathPlanner(Raven_Bot* owner);

  //creates an instance of the A* time-sliced search and registers it with
  //the path manager
  bool       RequestPathToItem(unsigned int ItemType);

  //creates an instance of the Dijkstra's time-sliced search and registers 
  //it with the path manager
  bool       RequestPathToPosition(Vector2D TargetPos);

  //called by an agent after it has been notified that a search has terminated
  //successfully. The method extracts the path from m_pCurrentSearch, adds
  //additional edges appropriate to the search type and returns it as a list of
  //PathEdges.
  Path       GetPath();

  //returns the cost to travel from the bot's current position to a specific 
  //graph node. This method makes use of the pre-calculated lookup table
  //created by Raven_Game
  double      GetCostToNode(unsigned int NodeIdx)const;

  //returns the cost to the closest instance of the GiverType. This method
  //also makes use of the pre-calculated lookup table. Returns -1 if no active
  //trigger found
  double      GetCostToClosestItem(unsigned int GiverType)const;

  
  //the path manager calls this to iterate once though the search cycle
  //of the currently assigned search algorithm. When a search is terminated
  //the method messages the owner with either the msg_NoPathAvailable or
  //msg_PathReady messages
  int        CycleOnce()const;

  Vector2D   GetDestination()const{return m_vDestinationPos;}
  void       SetDestination(Vector2D NewPos){m_vDestinationPos = NewPos;}

  //used to retrieve the position of a graph node from its index. (takes
  //into account the enumerations 'non_graph_source_node' and 
  //'non_graph_target_node'
  Vector2D  GetNodePosition(int idx)const;
};


#endif

