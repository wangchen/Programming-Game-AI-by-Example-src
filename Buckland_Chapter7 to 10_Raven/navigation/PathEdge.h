#ifndef PATHEDGE_H
#define PATHEDGE_H
//-----------------------------------------------------------------------------
//
//  Name:   PathEdge.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   class to represent a path edge. This path can be used by a path
//          planner in the creation of paths. 
//
//-----------------------------------------------------------------------------
#include "2d/vector2D.h"

class PathEdge
{
private:

  //positions of the source and destination nodes this edge connects
  Vector2D m_vSource;
  Vector2D m_vDestination;

  //the behavior associated with traversing this edge
  int      m_iBehavior;

  int      m_iDoorID;

public:
  
  PathEdge(Vector2D Source,
           Vector2D Destination,
           int      Behavior,
           int      DoorID = 0):m_vSource(Source),
                                m_vDestination(Destination),
                                m_iBehavior(Behavior),
                                m_iDoorID(DoorID)
  {}

  Vector2D Destination()const{return m_vDestination;}
  void     SetDestination(Vector2D NewDest){m_vDestination = NewDest;}
  
  Vector2D Source()const{return m_vSource;}
  void     SetSource(Vector2D NewSource){m_vSource = NewSource;}

  int      DoorID()const{return m_iDoorID;}
  int      Behavior()const{return m_iBehavior;}
};


#endif
