#include "Raven_PathPlanner.h"
#include "../Raven_Game.h"
#include "misc/utils.h"
#include "graph/GraphAlgorithms.h"
#include "misc/Cgdi.h"
#include "../Raven_Bot.h"
#include "../constants.h"
#include "../Raven_UserOptions.h"
#include "pathmanager.h"
#include "SearchTerminationPolicies.h"
#include "../lua/Raven_Scriptor.h"
#include "misc/CellSpacePartition.h"
#include "../Raven_Messages.h"
#include "Messaging/MessageDispatcher.h"
#include "graph/NodeTypeEnumerations.h"


#include "Debug/DebugConsole.h"
//#define SHOW_NAVINFO
#include <cassert>

//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Raven_PathPlanner::Raven_PathPlanner(Raven_Bot* owner):m_pOwner(owner),
               m_NavGraph(m_pOwner->GetWorld()->GetMap()->GetNavGraph()),
               m_pCurrentSearch(NULL)
{
}

//-------------------------- dtor ---------------------------------------------
//-----------------------------------------------------------------------------
Raven_PathPlanner::~Raven_PathPlanner()
{
  GetReadyForNewSearch();
}

//------------------------------ GetReadyForNewSearch -----------------------------------
//
//  called by the search manager when a search has been terminated to free
//  up the memory used when an instance of the search was created
//-----------------------------------------------------------------------------
void Raven_PathPlanner::GetReadyForNewSearch()
{
  //unregister any existing search with the path manager
  m_pOwner->GetWorld()->GetPathManager()->UnRegister(this);

  //clean up memory used by any existing search
  delete m_pCurrentSearch;    
  m_pCurrentSearch = 0;
}

//---------------------------- GetCostToNode ----------------------------------
//
//  returns the cost to travel from the bot's current position to a specific 
 // graph node. This method makes use of the pre-calculated lookup table
//-----------------------------------------------------------------------------
double Raven_PathPlanner::GetCostToNode(unsigned int NodeIdx)const
{
  //find the closest visible node to the bots position
  int nd = GetClosestNodeToPosition(m_pOwner->Pos());

  //add the cost to this node
  double cost =Vec2DDistance(m_pOwner->Pos(),
                            m_NavGraph.GetNode(nd).Pos());

  //add the cost to the target node and return
  return cost + m_pOwner->GetWorld()->GetMap()->CalculateCostToTravelBetweenNodes(nd, NodeIdx);
}

//------------------------ GetCostToClosestItem ---------------------------
//
//  returns the cost to the closest instance of the giver type. This method
//  makes use of the pre-calculated lookup table. Returns -1 if no active
//  trigger found
//-----------------------------------------------------------------------------
double Raven_PathPlanner::GetCostToClosestItem(unsigned int GiverType)const
{
  //find the closest visible node to the bots position
  int nd = GetClosestNodeToPosition(m_pOwner->Pos());

  //if no closest node found return failure
  if (nd == invalid_node_index) return -1;

  double ClosestSoFar = MaxDouble;

  //iterate through all the triggers to find the closest *active* trigger of 
  //type GiverType
  const Raven_Map::TriggerSystem::TriggerList& triggers = m_pOwner->GetWorld()->GetMap()->GetTriggers();

  Raven_Map::TriggerSystem::TriggerList::const_iterator it;
  for (it = triggers.begin(); it != triggers.end(); ++it)
  {
    if ( ((*it)->EntityType() == GiverType) && (*it)->isActive())
    {
      double cost = 
      m_pOwner->GetWorld()->GetMap()->CalculateCostToTravelBetweenNodes(nd,
                                                      (*it)->GraphNodeIndex());

      if (cost < ClosestSoFar)
      {
        ClosestSoFar = cost;
      }
    }
  }

  //return a negative value if no active trigger of the type found
  if (isEqual(ClosestSoFar, MaxDouble))
  {
    return -1;
  }

  return ClosestSoFar;
}


//----------------------------- GetPath ------------------------------------
//
//  called by an agent after it has been notified that a search has terminated
//  successfully. The method extracts the path from m_pCurrentSearch, adds
//  additional edges appropriate to the search type and returns it as a list of
//  PathEdges.
//-----------------------------------------------------------------------------
Raven_PathPlanner::Path Raven_PathPlanner::GetPath()
{
  assert (m_pCurrentSearch && 
          "<Raven_PathPlanner::GetPathAsNodes>: no current search");

  Path path =  m_pCurrentSearch->GetPathAsPathEdges();

  int closest = GetClosestNodeToPosition(m_pOwner->Pos());

  path.push_front(PathEdge(m_pOwner->Pos(),
                            GetNodePosition(closest),
                            NavGraphEdge::normal));

  
  //if the bot requested a path to a location then an edge leading to the
  //destination must be added
  if (m_pCurrentSearch->GetType() == Graph_SearchTimeSliced<EdgeType>::AStar)
  {   
    path.push_back(PathEdge(path.back().Destination(),
                            m_vDestinationPos,
                            NavGraphEdge::normal));
  }

  //smooth paths if required
  if (UserOptions->m_bSmoothPathsQuick)
  {
    SmoothPathEdgesQuick(path);
  }

  if (UserOptions->m_bSmoothPathsPrecise)
  {
    SmoothPathEdgesPrecise(path);
  }

  return path;
}

//--------------------------- SmoothPathEdgesQuick ----------------------------
//
//  smooths a path by removing extraneous edges.
//-----------------------------------------------------------------------------
void Raven_PathPlanner::SmoothPathEdgesQuick(Path& path)
{
  //create a couple of iterators and point them at the front of the path
  Path::iterator e1(path.begin()), e2(path.begin());

  //increment e2 so it points to the edge following e1.
  ++e2;

  //while e2 is not the last edge in the path, step through the edges checking
  //to see if the agent can move without obstruction from the source node of
  //e1 to the destination node of e2. If the agent can move between those 
  //positions then the two edges are replaced with a single edge.
  while (e2 != path.end())
  {
    //check for obstruction, adjust and remove the edges accordingly
    if ( (e2->Behavior() == EdgeType::normal) &&
          m_pOwner->canWalkBetween(e1->Source(), e2->Destination()) )
    {
      e1->SetDestination(e2->Destination());
      e2 = path.erase(e2);
    }

    else
    {
      e1 = e2;
      ++e2;
    }
  }
}


//----------------------- SmoothPathEdgesPrecise ---------------------------------
//
//  smooths a path by removing extraneous edges.
//-----------------------------------------------------------------------------
void Raven_PathPlanner::SmoothPathEdgesPrecise(Path& path)
{
  //create a couple of iterators
  Path::iterator e1, e2;

  //point e1 to the beginning of the path
  e1 = path.begin();
    
  while (e1 != path.end())
  {
    //point e2 to the edge immediately following e1
    e2 = e1; 
    ++e2;

    //while e2 is not the last edge in the path, step through the edges
    //checking to see if the agent can move without obstruction from the 
    //source node of e1 to the destination node of e2. If the agent can move
    //between those positions then the any edges between e1 and e2 are
    //replaced with a single edge.
    while (e2 != path.end())
    {
      //check for obstruction, adjust and remove the edges accordingly
      if ( (e2->Behavior() == EdgeType::normal) &&
            m_pOwner->canWalkBetween(e1->Source(), e2->Destination()) )
      {
        e1->SetDestination(e2->Destination());
        e2 = path.erase(++e1, ++e2);
        e1 = e2;
        --e1;
      }

      else
      {
        ++e2;
      }
    }

    ++e1;
  }
}



//---------------------------- CycleOnce --------------------------------------
//
//  the path manager calls this to iterate once though the search cycle
//  of the currently assigned search algorithm.
//-----------------------------------------------------------------------------
int Raven_PathPlanner::CycleOnce()const
{
  assert (m_pCurrentSearch && "<Raven_PathPlanner::CycleOnce>: No search object instantiated");

  int result = m_pCurrentSearch->CycleOnce();

  //let the bot know of the failure to find a path
  if (result == target_not_found)
  {
     Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                             SENDER_ID_IRRELEVANT,
                             m_pOwner->ID(),
                             Msg_NoPathAvailable,
                             NO_ADDITIONAL_INFO);

  }

  //let the bot know a path has been found
  else if (result == target_found)
  {
    //if the search was for an item type then the final node in the path will
    //represent a giver trigger. Consequently, it's worth passing the pointer
    //to the trigger in the extra info field of the message. (The pointer
    //will just be NULL if no trigger)
    void* pTrigger = 
    m_NavGraph.GetNode(m_pCurrentSearch->GetPathToTarget().back()).ExtraInfo();

    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            SENDER_ID_IRRELEVANT,
                            m_pOwner->ID(),
                            Msg_PathReady,
                            pTrigger);
  }

  return result;
}

//------------------------ GetClosestNodeToPosition ---------------------------
//
//  returns the index of the closest visible graph node to the given position
//-----------------------------------------------------------------------------
int Raven_PathPlanner::GetClosestNodeToPosition(Vector2D pos)const
{
  double ClosestSoFar = MaxDouble;
  int   ClosestNode  = no_closest_node_found;

  //when the cell space is queried this the the range searched for neighboring
  //graph nodes. This value is inversely proportional to the density of a 
  //navigation graph (less dense = bigger values)
  const double range = m_pOwner->GetWorld()->GetMap()->GetCellSpaceNeighborhoodRange();

  //calculate the graph nodes that are neighboring this position
  m_pOwner->GetWorld()->GetMap()->GetCellSpace()->CalculateNeighbors(pos, range);

  //iterate through the neighbors and sum up all the position vectors
  for (NodeType* pN = m_pOwner->GetWorld()->GetMap()->GetCellSpace()->begin();
                 !m_pOwner->GetWorld()->GetMap()->GetCellSpace()->end();     
                 pN = m_pOwner->GetWorld()->GetMap()->GetCellSpace()->next())
  {
    //if the path between this node and pos is unobstructed calculate the
    //distance
    if (m_pOwner->canWalkBetween(pos, pN->Pos()))
    {
      double dist = Vec2DDistanceSq(pos, pN->Pos());

      //keep a record of the closest so far
      if (dist < ClosestSoFar)
      {
        ClosestSoFar = dist;
        ClosestNode  = pN->Index();
      }
    }
  }
   
  return ClosestNode;
}

//--------------------------- RequestPathToPosition ------------------------------
//
//  Given a target, this method first determines if nodes can be reached from 
//  the  bot's current position and the target position. If either end point
//  is unreachable the method returns false. 
//
//  If nodes are reachable from both positions then an instance of the time-
//  sliced A* search is created and registered with the search manager. the
//  method then returns true.
//        
//-----------------------------------------------------------------------------
bool Raven_PathPlanner::RequestPathToPosition(Vector2D TargetPos)
{ 
  #ifdef SHOW_NAVINFO
    debug_con << "------------------------------------------------" << "";
#endif
  GetReadyForNewSearch();

  //make a note of the target position.
  m_vDestinationPos = TargetPos;

  //if the target is walkable from the bot's position a path does not need to
  //be calculated, the bot can go straight to the position by ARRIVING at
  //the current waypoint
  if (m_pOwner->canWalkTo(TargetPos))
  { 
    return true;
  }
  
  //find the closest visible node to the bots position
  int ClosestNodeToBot = GetClosestNodeToPosition(m_pOwner->Pos());

  //remove the destination node from the list and return false if no visible
  //node found. This will occur if the navgraph is badly designed or if the bot
  //has managed to get itself *inside* the geometry (surrounded by walls),
  //or an obstacle.
  if (ClosestNodeToBot == no_closest_node_found)
  { 
#ifdef SHOW_NAVINFO
    debug_con << "No closest node to bot found!" << "";
#endif

    return false; 
  }

  #ifdef SHOW_NAVINFO
    debug_con << "Closest node to bot is " << ClosestNodeToBot << "";
#endif

  //find the closest visible node to the target position
  int ClosestNodeToTarget = GetClosestNodeToPosition(TargetPos);
  
  //return false if there is a problem locating a visible node from the target.
  //This sort of thing occurs much more frequently than the above. For
  //example, if the user clicks inside an area bounded by walls or inside an
  //object.
  if (ClosestNodeToTarget == no_closest_node_found)
  { 
#ifdef SHOW_NAVINFO
    debug_con << "No closest node to target (" << ClosestNodeToTarget << ") found!" << "";
#endif

    return false; 
  }

  #ifdef SHOW_NAVINFO
    debug_con << "Closest node to target is " << ClosestNodeToTarget << "";
#endif

  //create an instance of a the distributed A* search class
  typedef Graph_SearchAStar_TS<Raven_Map::NavGraph, Heuristic_Euclid> AStar;
   
  m_pCurrentSearch = new AStar(m_NavGraph,
                               ClosestNodeToBot,
                               ClosestNodeToTarget);

  //and register the search with the path manager
  m_pOwner->GetWorld()->GetPathManager()->Register(this);

  return true;
}


//------------------------------ RequestPathToItem -----------------------------
//
// Given an item type, this method determines the closest reachable graph node
// to the bot's position and then creates a instance of the time-sliced 
// Dijkstra's algorithm, which it registers with the search manager
//
//-----------------------------------------------------------------------------
bool Raven_PathPlanner::RequestPathToItem(unsigned int ItemType)
{    
  //clear the waypoint list and delete any active search
  GetReadyForNewSearch();

  //find the closest visible node to the bots position
  int ClosestNodeToBot = GetClosestNodeToPosition(m_pOwner->Pos());

  //remove the destination node from the list and return false if no visible
  //node found. This will occur if the navgraph is badly designed or if the bot
  //has managed to get itself *inside* the geometry (surrounded by walls),
  //or an obstacle
  if (ClosestNodeToBot == no_closest_node_found)
  { 
#ifdef SHOW_NAVINFO
    debug_con << "No closest node to bot found!" << "";
#endif

    return false; 
  }

  //create an instance of the search algorithm
  typedef FindActiveTrigger<Trigger<Raven_Bot> > t_con; 
  typedef Graph_SearchDijkstras_TS<Raven_Map::NavGraph, t_con> DijSearch;
  
  m_pCurrentSearch = new DijSearch(m_NavGraph,
                                   ClosestNodeToBot,
                                   ItemType);  

  //register the search with the path manager
  m_pOwner->GetWorld()->GetPathManager()->Register(this);

  return true;
}

//------------------------------ GetNodePosition ------------------------------
//
//  used to retrieve the position of a graph node from its index. (takes
//  into account the enumerations 'non_graph_source_node' and 
//  'non_graph_target_node'
//----------------------------------------------------------------------------- 
Vector2D Raven_PathPlanner::GetNodePosition(int idx)const
{
  return m_NavGraph.GetNode(idx).Pos();
}
  
 


