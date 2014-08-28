#ifndef GRAPH_NODE_TYPES_H
#define GRAPH_NODE_TYPES_H
//-----------------------------------------------------------------------------
//
//  Name:   GraphNodeTypes.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Node classes to be used with graphs
//-----------------------------------------------------------------------------
#include <list>
#include <ostream>
#include <fstream>
#include "2D/Vector2D.h"
#include "graph/NodeTypeEnumerations.h"




class GraphNode
{  
protected:

  //every node has an index. A valid index is >= 0
  int        m_iIndex;

public:
  
  GraphNode():m_iIndex(invalid_node_index){}
  GraphNode(int idx):m_iIndex(idx){}
  GraphNode(std::ifstream& stream){char buffer[50]; stream >> buffer >> m_iIndex;}

  virtual ~GraphNode(){}

  int  Index()const{return m_iIndex;}
  void SetIndex(int NewIndex){m_iIndex = NewIndex;}
  


  //for reading and writing to streams.
  friend std::ostream& operator<<(std::ostream& os, const GraphNode& n)
  {
    os << "Index: " << n.m_iIndex << std::endl; return os;
  }

};   



//-----------------------------------------------------------------------------
//
//  Graph node for use in creating a navigation graph.This node contains
//  the position of the node and a pointer to a BaseGameEntity... useful
//  if you want your nodes to represent health packs, gold mines and the like
//-----------------------------------------------------------------------------
template <class extra_info = void*>
class NavGraphNode : public GraphNode
{
protected:

  //the node's position
  Vector2D     m_vPosition;

  //often you will require a navgraph node to contain additional information.
  //For example a node might represent a pickup such as armor in which
  //case m_ExtraInfo could be an enumerated value denoting the pickup type,
  //thereby enabling a search algorithm to search a graph for specific items.
  //Going one step further, m_ExtraInfo could be a pointer to the instance of
  //the item type the node is twinned with. This would allow a search algorithm
  //to test the status of the pickup during the search. 
  extra_info  m_ExtraInfo;

public:
  
  //ctors
  NavGraphNode():m_ExtraInfo(extra_info()){}

  NavGraphNode(int      idx,
               Vector2D pos):GraphNode(idx),
                             m_vPosition(pos),
                             m_ExtraInfo(extra_info())
  {}

  //stream constructor
  NavGraphNode(std::ifstream& stream):m_ExtraInfo(extra_info())
  {
    char buffer[50];
    stream >> buffer >> m_iIndex >> buffer >> m_vPosition.x >> buffer >> m_vPosition.y;
  }
 

  virtual ~NavGraphNode(){}

  Vector2D   Pos()const{return m_vPosition;}
  void       SetPos(Vector2D NewPosition){m_vPosition = NewPosition;}

  extra_info ExtraInfo()const{return m_ExtraInfo;}
  void       SetExtraInfo(extra_info info){m_ExtraInfo = info;}

  //for reading and writing to streams.
  friend std::ostream& operator<<(std::ostream& os, const NavGraphNode& n)
  {
    os << "Index: " << n.m_iIndex << " PosX: " << n.m_vPosition.x << " PosY: " << n.m_vPosition.y << std::endl;

    return os;
  }
  
};


#endif
