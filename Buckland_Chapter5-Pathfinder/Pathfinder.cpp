#include "Pathfinder.h"

#include <iostream>

#include "Graph/HandyGraphFunctions.h"
#include "Time/PrecisionTimer.h"
#include "constants.h"
#include "graph/AStarHeuristicPolicies.h"
#include "misc/Cgdi.h"
#include "misc/Stream_Utility_Functions.h"
using namespace std;

extern HWND g_hwndToolbar;
extern const char * g_szApplicationName;
extern const char * g_szWindowClassName;

//----------------------- CreateGraph ------------------------------------
//
//------------------------------------------------------------------------
void Pathfinder::CreateGraph(int CellsUp, int CellsAcross)
{
  //get the height of the toolbar
  RECT rectToolbar;
  GetWindowRect(g_hwndToolbar, &rectToolbar);

  //get the dimensions of the client area
  HWND hwndMainWindow = FindWindow(g_szWindowClassName, g_szApplicationName);

  RECT rect;
  GetClientRect(hwndMainWindow, &rect);
  m_icxClient = rect.right;
  m_icyClient = rect.bottom - abs(rectToolbar.bottom - rectToolbar.top) - InfoWindowHeight;

  //initialize the terrain vector with normal terrain
  m_TerrainType.assign(CellsUp * CellsAcross, normal);

  m_iCellsX = CellsAcross;
  m_iCellsY = CellsUp;
  m_dCellWidth = (double)m_icxClient / (double)CellsAcross;
  m_dCellHeight = (double)m_icyClient / (double)CellsUp;

  //delete any old graph
  delete m_pGraph;

  //create the graph
  m_pGraph = new NavGraph(false);  //not a digraph

  GraphHelper_CreateGrid(*m_pGraph, m_icxClient, m_icyClient, CellsUp, CellsAcross);

  //initialize source and target indexes to mid top and bottom of grid
  PointToIndex(VectorToPOINTS(Vector2D(m_icxClient / 2, m_dCellHeight * 2)), m_iTargetCell);
  PointToIndex(
    VectorToPOINTS(Vector2D(m_icxClient / 2, m_icyClient - m_dCellHeight * 2)), m_iSourceCell);

  m_Path.clear();
  m_SubTree.clear();

  m_CurrentAlgorithm = non;
  m_dTimeTaken = 0;
}

//--------------------- PointToIndex -------------------------------------
//
//  converts a POINTS into an index into the graph
//------------------------------------------------------------------------
bool Pathfinder::PointToIndex(POINTS p, int & NodeIndex)
{
  //convert p to an index into the graph
  int x = (int)((double)(p.x) / m_dCellWidth);
  int y = (int)((double)(p.y) / m_dCellHeight);

  //make sure the values are legal
  if ((x > m_iCellsX) || (y > m_iCellsY)) {
    NodeIndex = -1;

    return false;
  }

  NodeIndex = y * m_iCellsX + x;

  return true;
}

//----------------- GetTerrainCost ---------------------------------------
//
//  returns the cost of the terrain represented by the current brush type
//------------------------------------------------------------------------
double Pathfinder::GetTerrainCost(const brush_type brush)
{
  const double cost_normal = 1.0;
  const double cost_water = 2.0;
  const double cost_mud = 1.5;

  switch (brush) {
    case normal:
      return cost_normal;
    case water:
      return cost_water;
    case mud:
      return cost_mud;
    default:
      return MaxDouble;
  };
}

//----------------------- PaintTerrain -----------------------------------
//
//  this either changes the terrain at position p to whatever the current
//  terrain brush is set to, or it adjusts the source/target cell
//------------------------------------------------------------------------
void Pathfinder::PaintTerrain(POINTS p)
{
  //convert p to an index into the graph
  int x = (int)((double)(p.x) / m_dCellWidth);
  int y = (int)((double)(p.y) / m_dCellHeight);

  //make sure the values are legal
  if ((x > m_iCellsX) || (y > (m_iCellsY - 1))) return;

  //reset path and tree records
  m_SubTree.clear();
  m_Path.clear();

  //if the current terrain brush is set to either source or target we
  //should change the appropriate node
  if ((m_CurrentTerrainBrush == source) || (m_CurrentTerrainBrush == target)) {
    switch (m_CurrentTerrainBrush) {
      case source:

        m_iSourceCell = y * m_iCellsX + x;
        break;

      case target:

        m_iTargetCell = y * m_iCellsX + x;
        break;

    }  //end switch
  }

  //otherwise, change the terrain at the current mouse position
  else {
    UpdateGraphFromBrush(m_CurrentTerrainBrush, y * m_iCellsX + x);
  }

  //update any currently selected algorithm
  UpdateAlgorithm();
}

//--------------------------- UpdateGraphFromBrush ----------------------------
//
//  given a brush and a node index, this method updates the graph appropriately
//  (by removing/adding nodes or changing the costs of the node's edges)
//-----------------------------------------------------------------------------
void Pathfinder::UpdateGraphFromBrush(int brush, int CellIndex)
{
  //set the terrain type in the terrain index
  m_TerrainType[CellIndex] = brush;

  //if current brush is an obstacle then this node must be removed
  //from the graph
  if (brush == 1) {
    m_pGraph->RemoveNode(CellIndex);
  }

  else {
    //make the node active again if it is currently inactive
    if (!m_pGraph->isNodePresent(CellIndex)) {
      int y = CellIndex / m_iCellsY;
      int x = CellIndex - (y * m_iCellsY);

      m_pGraph->AddNode(NavGraph::NodeType(
        CellIndex,
        Vector2D(x * m_dCellWidth + m_dCellWidth / 2.0, y * m_dCellHeight + m_dCellHeight / 2.0)));

      GraphHelper_AddAllNeighboursToGridNode(*m_pGraph, y, x, m_iCellsX, m_iCellsY);
    }

    //set the edge costs in the graph
    WeightNavGraphNodeEdges(*m_pGraph, CellIndex, GetTerrainCost((brush_type)brush));
  }
}

//--------------------------- UpdateAlgorithm ---------------------------------
void Pathfinder::UpdateAlgorithm()
{
  //update any current algorithm
  switch (m_CurrentAlgorithm) {
    case non:

      break;

    case search_dfs:

      CreatePathDFS();
      break;

    case search_bfs:

      CreatePathBFS();
      break;

    case search_dijkstra:

      CreatePathDijkstra();
      break;

    case search_astar:

      CreatePathAStar();
      break;

    default:
      break;
  }
}

//------------------------- CreatePathDFS --------------------------------
//
//  uses DFS to find a path between the start and target cells.
//  Stores the path as a series of node indexes in m_Path.
//------------------------------------------------------------------------
void Pathfinder::CreatePathDFS()
{
  //set current algorithm
  m_CurrentAlgorithm = search_dfs;

  //clear any existing path
  m_Path.clear();
  m_SubTree.clear();

  //create and start a timer
  PrecisionTimer timer;
  timer.Start();

  //do the search
  Graph_SearchDFS<NavGraph> DFS(*m_pGraph, m_iSourceCell, m_iTargetCell);

  //record the time taken
  m_dTimeTaken = timer.TimeElapsed();

  //now grab the path (if one has been found)
  if (DFS.Found()) {
    m_Path = DFS.GetPathToTarget();
  }

  m_SubTree = DFS.GetSearchTree();

  m_dCostToTarget = 0.0;
}

//------------------------- CreatePathBFS --------------------------------
//
//  uses BFS to find a path between the start and target cells.
//  Stores the path as a series of node indexes in m_Path.
//------------------------------------------------------------------------
void Pathfinder::CreatePathBFS()
{
  //set current algorithm
  m_CurrentAlgorithm = search_bfs;

  //clear any existing path
  m_Path.clear();
  m_SubTree.clear();

  //create and start a timer
  PrecisionTimer timer;
  timer.Start();

  //do the search
  Graph_SearchBFS<NavGraph> BFS(*m_pGraph, m_iSourceCell, m_iTargetCell);

  //record the time taken
  m_dTimeTaken = timer.TimeElapsed();

  //now grab the path (if one has been found)
  if (BFS.Found()) {
    m_Path = BFS.GetPathToTarget();
  }

  m_SubTree = BFS.GetSearchTree();

  m_dCostToTarget = 0.0;
}

//-------------------------- CreatePathDijkstra --------------------------
//
//  creates a path from m_iSourceCell to m_iTargetCell using Dijkstra's algorithm
//------------------------------------------------------------------------
void Pathfinder::CreatePathDijkstra()
{
  //set current algorithm
  m_CurrentAlgorithm = search_dijkstra;

  //create and start a timer
  PrecisionTimer timer;
  timer.Start();

  Graph_SearchDijkstra<NavGraph> djk(*m_pGraph, m_iSourceCell, m_iTargetCell);

  //record the time taken
  m_dTimeTaken = timer.TimeElapsed();

  m_Path = djk.GetPathToTarget();

  m_SubTree = djk.GetSPT();

  m_dCostToTarget = djk.GetCostToTarget();
}

//--------------------------- CreatePathAStar ---------------------------
//------------------------------------------------------------------------
void Pathfinder::CreatePathAStar()
{
  //set current algorithm
  m_CurrentAlgorithm = search_astar;

  //create and start a timer
  PrecisionTimer timer;
  timer.Start();

  //create a couple of typedefs so the code will sit comfortably on the page
  typedef Graph_SearchAStar<NavGraph, Heuristic_Euclid> AStarSearch;

  //create an instance of the A* search using the Euclidean heuristic
  AStarSearch AStar(*m_pGraph, m_iSourceCell, m_iTargetCell);

  //record the time taken
  m_dTimeTaken = timer.TimeElapsed();

  m_Path = AStar.GetPathToTarget();

  m_SubTree = AStar.GetSPT();

  m_dCostToTarget = AStar.GetCostToTarget();
}

//---------------------------Load n save methods ------------------------------
//-----------------------------------------------------------------------------
void Pathfinder::Save(char * FileName)
{
  ofstream save(FileName);
  assert(save && "Pathfinder::Save< bad file >");

  //save the size of the grid
  save << m_iCellsX << endl;
  save << m_iCellsY << endl;

  //save the terrain
  for (unsigned int t = 0; t < m_TerrainType.size(); ++t) {
    if (t == m_iSourceCell) {
      save << source << endl;
    } else if (t == m_iTargetCell) {
      save << target << endl;
    } else {
      save << m_TerrainType[t] << endl;
    }
  }
}

//-------------------------------- Load ---------------------------------------
//-----------------------------------------------------------------------------
void Pathfinder::Load(char * FileName)
{
  ifstream load(FileName);
  assert(load && "Pathfinder::Save< bad file >");

  //load the size of the grid
  load >> m_iCellsX;
  load >> m_iCellsY;

  //create a graph of the correct size
  CreateGraph(m_iCellsY, m_iCellsX);

  int terrain;

  //save the terrain
  for (int t = 0; t < m_iCellsX * m_iCellsY; ++t) {
    load >> terrain;

    if (terrain == source) {
      m_iSourceCell = t;
    }

    else if (terrain == target) {
      m_iTargetCell = t;
    }

    else {
      m_TerrainType[t] = terrain;

      UpdateGraphFromBrush(terrain, t);
    }
  }
}

//------------------------ GetNameOfCurrentSearchAlgorithm --------------------
//-----------------------------------------------------------------------------
std::string Pathfinder::GetNameOfCurrentSearchAlgorithm() const
{
  switch (m_CurrentAlgorithm) {
    case non:
      return "";
    case search_astar:
      return "A Star";
    case search_bfs:
      return "Breadth First";
    case search_dfs:
      return "Depth First";
    case search_dijkstra:
      return "Dijkstras";
  }
}

//---------------------------- Render ------------------------------------
//
//------------------------------------------------------------------------
void Pathfinder::Render()
{
  gdi->TransparentText();

  //render all the cells
  for (int nd = 0; nd < m_pGraph->NumNodes(); ++nd) {
    int left = (int)(m_pGraph->GetNode(nd).Pos().x - m_dCellWidth / 2.0);
    int top = (int)(m_pGraph->GetNode(nd).Pos().y - m_dCellHeight / 2.0);
    int right = (int)(1 + m_pGraph->GetNode(nd).Pos().x + m_dCellWidth / 2.0);
    int bottom = (int)(1 + m_pGraph->GetNode(nd).Pos().y + m_dCellHeight / 2.0);

    gdi->GreyPen();

    switch (m_TerrainType[nd]) {
      case 0:
        gdi->WhiteBrush();
        if (!m_bShowTiles) gdi->WhitePen();
        break;

      case 1:
        gdi->BlackBrush();
        if (!m_bShowTiles) gdi->BlackPen();
        break;

      case 2:
        gdi->LightBlueBrush();
        if (!m_bShowTiles) gdi->LightBluePen();
        break;

      case 3:
        gdi->BrownBrush();
        if (!m_bShowTiles) gdi->BrownPen();
        break;

      default:
        gdi->WhiteBrush();
        if (!m_bShowTiles) gdi->WhitePen();
        break;

    }  //end switch

    if (nd == m_iTargetCell) {
      gdi->RedBrush();
      if (!m_bShowTiles) gdi->RedPen();
    }

    if (nd == m_iSourceCell) {
      gdi->GreenBrush();
      if (!m_bShowTiles) gdi->GreenPen();
    }

    gdi->Rect(left, top, right, bottom);

    if (nd == m_iTargetCell) {
      gdi->ThickBlackPen();
      gdi->Cross(
        Vector2D(m_pGraph->GetNode(nd).Pos().x - 1, m_pGraph->GetNode(nd).Pos().y - 1),
        (int)((m_dCellWidth * 0.6) / 2.0));
    }

    if (nd == m_iSourceCell) {
      gdi->ThickBlackPen();
      gdi->HollowBrush();
      gdi->Rect(left + 7, top + 7, right - 6, bottom - 6);
    }

    //render dots at the corners of the cells
    gdi->DrawDot(left, top, RGB(0, 0, 0));
    gdi->DrawDot(right - 1, top, RGB(0, 0, 0));
    gdi->DrawDot(left, bottom - 1, RGB(0, 0, 0));
    gdi->DrawDot(right - 1, bottom - 1, RGB(0, 0, 0));
  }
  //draw the graph nodes and edges if rqd
  if (m_bShowGraph) {
    GraphHelper_DrawUsingGDI<NavGraph>(
      *m_pGraph, Cgdi::light_grey, false);  //false = don't draw node IDs
  }

  //draw any tree retrieved from the algorithms
  gdi->RedPen();

  for (unsigned int e = 0; e < m_SubTree.size(); ++e) {
    if (m_SubTree[e]) {
      Vector2D from = m_pGraph->GetNode(m_SubTree[e]->From()).Pos();
      Vector2D to = m_pGraph->GetNode(m_SubTree[e]->To()).Pos();

      gdi->Line(from, to);
    }
  }

  //draw the path (if any)
  if (m_Path.size() > 0) {
    gdi->ThickBluePen();

    std::list<int>::iterator it = m_Path.begin();
    std::list<int>::iterator nxt = it;
    ++nxt;

    for (it; nxt != m_Path.end(); ++it, ++nxt) {
      gdi->Line(m_pGraph->GetNode(*it).Pos(), m_pGraph->GetNode(*nxt).Pos());
    }
  }

  if (m_dTimeTaken) {
    //draw time taken to complete algorithm
    string time = ttos(m_dTimeTaken, 8);
    string s = "Time Elapsed for " + GetNameOfCurrentSearchAlgorithm() + " is " + time;
    gdi->TextAtPos(1, m_icyClient + 3, s);
  }

  //display the total path cost if appropriate
  if (m_CurrentAlgorithm == search_astar || m_CurrentAlgorithm == search_dijkstra) {
    gdi->TextAtPos(m_icxClient - 110, m_icyClient + 3, "Cost is " + ttos(m_dCostToTarget));
  }
}
