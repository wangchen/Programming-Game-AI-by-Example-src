#ifndef GRAPH_EDGE_TYPES_H
#define GRAPH_EDGE_TYPES_H
//-----------------------------------------------------------------------------
//
//  Name:   GraphEdgeTypes.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Class to define an edge connecting two nodes.
//          
//          An edge has an associated cost.
//-----------------------------------------------------------------------------
#include <ostream>
#include <fstream>

#include "graph/NodeTypeEnumerations.h"


class GraphEdge
{
protected:

  //An edge connects two nodes. Valid node indices are always positive.
  int     m_iFrom;
  int     m_iTo;

  //the cost of traversing the edge
  double  m_dCost;

public:

  //ctors
  GraphEdge(int from, int to, double cost):m_dCost(cost),
                                           m_iFrom(from),
                                           m_iTo(to)
  {}
  
  GraphEdge(int from, int  to):m_dCost(1.0),
                               m_iFrom(from),
                               m_iTo(to)
  {}
  
  GraphEdge():m_dCost(1.0),
              m_iFrom(invalid_node_index),
              m_iTo(invalid_node_index)
  {}

  //stream constructor
  GraphEdge(std::ifstream& stream)
  {
    char buffer[50];
    stream  >> buffer >> m_iFrom >> buffer >> m_iTo >> buffer >> m_dCost;
  }

  virtual ~GraphEdge(){}

  int   From()const{return m_iFrom;}
  void  SetFrom(int NewIndex){m_iFrom = NewIndex;}

  int   To()const{return m_iTo;}
  void  SetTo(int NewIndex){m_iTo = NewIndex;}

  double Cost()const{return m_dCost;}
  void  SetCost(double NewCost){m_dCost = NewCost;}


  //these two operators are required
  bool operator==(const GraphEdge& rhs)
  {
    return rhs.m_iFrom == this->m_iFrom &&
           rhs.m_iTo   == this->m_iTo   &&
           rhs.m_dCost == this->m_dCost;
  }

  bool operator!=(const GraphEdge& rhs)
  {
    return !(*this == rhs);
  }

  //for reading and writing to streams.
  friend std::ostream& operator<<(std::ostream& os, const GraphEdge& e)
  {
    os << "m_iFrom: " << e.m_iFrom << " m_iTo: " << e.m_iTo 
       << " m_dCost: " << e.m_dCost << std::endl;
    
    return os;
  }

};


class NavGraphEdge : public GraphEdge
{
public:
  
  //examples of typical flags
  enum
  {
    normal            = 0,
    swim              = 1 << 0,
    crawl             = 1 << 1,
    creep             = 1 << 3,
    jump              = 1 << 3,
    fly               = 1 << 4,
    grapple           = 1 << 5,
    goes_through_door = 1 << 6
  };

protected:

  int   m_iFlags;

  //if this edge intersects with an object (such as a door or lift), then
  //this is that object's ID. 
  int  m_iIDofIntersectingEntity;

public:
 
  
  NavGraphEdge(int    from,
               int    to,
               double cost,
               int    flags = 0,
               int    id = -1):GraphEdge(from,to,cost),
                               m_iFlags(flags),
                               m_iIDofIntersectingEntity(id)

  {} 


  //stream constructor
  NavGraphEdge(std::ifstream& stream)
  {
    char buffer[50];
    stream  >> buffer >> m_iFrom >> buffer >> m_iTo >> buffer >> m_dCost;
    stream >> buffer >> m_iFlags >> buffer >> m_iIDofIntersectingEntity;
  }

  int  Flags()const{return m_iFlags;}
  void SetFlags(int flags){m_iFlags = flags;}
  
  int  IDofIntersectingEntity()const{return m_iIDofIntersectingEntity;}
  void SetIDofIntersectingEntity(int id){m_iIDofIntersectingEntity = id;}

 
  friend std::ostream& operator<<(std::ostream& os, const NavGraphEdge& e)
  {
    os << "m_iFrom: " << e.m_iFrom << " m_iTo: " << e.m_iTo 
       << " m_dCost: " << e.m_dCost << " m_iFlags: " << e.m_iFlags
       << " ID: " << e.m_iIDofIntersectingEntity << std::endl;
    
    return os;
  }
};


#endif