#ifndef Pathfinder_H
#define Pathfinder_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   Pathfinder.h
//
//  Desc:   class enabling users to create simple environments consisting
//          of different terrain types and then to use various search algorithms
//          to find paths through them
//
//  Author: Mat Buckland  (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <list>


#include "2D/Vector2d.h"
#include "Graph/SparseGraph.h"
#include "Graph/GraphAlgorithms.h"
#include "misc/utils.h"
#include "graph/GraphEdgeTypes.h"
#include "graph/GraphNodeTypes.h"



class Pathfinder
{
public:

  enum brush_type
  {
    normal   = 0,
    obstacle = 1,
    water    = 2,
    mud      = 3,
    source   = 4,
    target   = 5
  };
      
  enum algorithm_type
  {
    non,
    search_astar,
    search_bfs,
    search_dfs,
    search_dijkstra
  };

private:
  
  //the terrain type of each cell
  std::vector<int>              m_TerrainType;

  //this vector will store any path returned from a graph search
  std::list<int>                m_Path;

  //create a typedef for the graph type
  typedef SparseGraph<NavGraphNode<void*>, GraphEdge> NavGraph;

  NavGraph*                     m_pGraph;
  
  //this vector of edges is used to store any subtree returned from 
  //any of the graph algorithms (such as an SPT)
  std::vector<const GraphEdge*> m_SubTree;

  //the total cost of the path from target to source
  double                         m_dCostToTarget;

  //the currently selected algorithm
  algorithm_type                m_CurrentAlgorithm;

  //the current terrain brush
  brush_type                    m_CurrentTerrainBrush;

  //the dimensions of the cells
  double                        m_dCellWidth;
  double                        m_dCellHeight;

  //number of cells vertically and horizontally
  int                           m_iCellsX,
                                m_iCellsY;

  //local record of the client area
  int                           m_icxClient,
                                m_icyClient;

  //the indices of the source and target cells
  int                           m_iSourceCell,
                                m_iTargetCell;

  //flags to indicate if the start and finish points have been added
  bool                          m_bStart,
                                m_bFinish;

  //should the graph (nodes and GraphEdges) be rendered?
  bool                          m_bShowGraph;

  //should the tile outlines be rendered
  bool                          m_bShowTiles;

  //holds the time taken for the most currently used algorithm to
  //complete
  double                        m_dTimeTaken;
  
  //this calls the appropriate algorithm
  void  UpdateAlgorithm();

  //helper function for PaintTerrain (see below)
  void  UpdateGraphFromBrush(int brush, int CellIndex);
 
 std::string GetNameOfCurrentSearchAlgorithm()const;

public:

  Pathfinder():m_bStart(false),
                m_bFinish(false),
                m_bShowGraph(false),
                m_bShowTiles(true),
                m_dCellWidth(0),
                m_dCellHeight(0),
                m_iCellsX(0),
                m_iCellsY(0),
                m_dTimeTaken(0.0),
                m_CurrentTerrainBrush(normal),
                m_iSourceCell(0),
                m_iTargetCell(0),
                m_icxClient(0),
                m_icyClient(0),
                m_dCostToTarget(0.0),
                m_pGraph(NULL)
  {}

  ~Pathfinder(){delete m_pGraph;}

  void CreateGraph(int CellsUp, int CellsAcross);

  void Render();

  //this will paint whatever cell the cursor is currently over in the 
  //currently selected terrain brush
  void PaintTerrain(POINTS p);

  //the algorithms
  void CreatePathDFS();
  void CreatePathBFS();
  void CreatePathDijkstra();
  void CreatePathAStar();
  void MinSpanningTree();

  //if m_bShowGraph is true the graph will be rendered
  void ToggleShowGraph(){m_bShowGraph = !m_bShowGraph;}
  void SwitchGraphOn(){m_bShowGraph = true;}
  void SwitchGraphOff(){m_bShowGraph = false;}
  bool isShowGraphOn()const{return m_bShowGraph;}

  void ToggleShowTiles(){m_bShowTiles = !m_bShowTiles;}
  void SwitchTilesOn(){m_bShowTiles = true;}
  void SwitchTilesOff(){m_bShowTiles = false;}
  bool isShowTilesOn()const{return m_bShowTiles;}

  void ChangeBrush(const brush_type NewBrush){m_CurrentTerrainBrush = NewBrush;}

  void ChangeSource(const int cell){m_iSourceCell = cell;}
  void ChangeTarget(const int cell){m_iTargetCell = cell;}

  //converts a POINTS to an index into the graph. Returns false if p
  //is invalid
  bool PointToIndex(POINTS p, int& NodeIndex);

  //returns the terrain cost of the brush type
  double GetTerrainCost(brush_type brush);

  void Save( char* FileName);
  void Load( char* FileName);

};


#endif