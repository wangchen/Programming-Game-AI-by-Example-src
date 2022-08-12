#ifndef PATH_H
#define PATH_H
//------------------------------------------------------------------------
//
//  Name:   Path.h
//
//  Desc:   class to define, manage, and traverse a path (defined by a series of 2D vectors)
//          
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <list>
#include <cassert>

#include "2d/Vector2D.h"




class Path
{
private:
  
  std::list<Vector2D>            m_WayPoints;

  //points to the current waypoint
  std::list<Vector2D>::iterator  curWaypoint;

  //flag to indicate if the path should be looped
  //(The last waypoint connected to the first)
  bool                           m_bLooped;

public:
  
  Path():m_bLooped(false), curWaypoint(NULL){}

  //constructor for creating a path with initial random waypoints. MinX/Y
  //& MaxX/Y define the bounding box of the path.
  Path(int    NumWaypoints,
       double MinX,
       double MinY,
       double MaxX,
       double MaxY,
       bool   looped):m_bLooped(looped)
  {
    CreateRandomPath(NumWaypoints, MinX, MinY, MaxX, MaxY);

    curWaypoint = m_WayPoints.begin();
  }


  //returns the current waypoint
  Vector2D    CurrentWaypoint()const{assert(curWaypoint != NULL); return *curWaypoint;}

  //returns true if the end of the list has been reached
  bool        Finished(){return !(curWaypoint != m_WayPoints.end());}
  
  //moves the iterator on to the next waypoint in the list
  inline void SetNextWaypoint();

  //creates a random path which is bound by rectangle described by
  //the min/max values
  std::list<Vector2D> CreateRandomPath(int    NumWaypoints,
                                       double MinX,
                                       double MinY,
                                       double MaxX,
                                       double MaxY);


  void LoopOn(){m_bLooped = true;}
  void LoopOff(){m_bLooped = false;}
 
  //adds a waypoint to the end of the path
  void AddWayPoint(Vector2D new_point);

  //methods for setting the path with either another Path or a list of vectors
  void Set(std::list<Vector2D> new_path){m_WayPoints = new_path;curWaypoint = m_WayPoints.begin();}
  void Set(const Path& path){m_WayPoints=path.GetPath(); curWaypoint = m_WayPoints.begin();}
  

  void Clear(){m_WayPoints.clear();}

  std::list<Vector2D> GetPath()const{return m_WayPoints;}

  //renders the path in orange
  void Render()const; 
};




//-------------------- Methods -------------------------------------------

inline void Path::SetNextWaypoint()
{
  assert (m_WayPoints.size() > 0);
    
  if (++curWaypoint == m_WayPoints.end())
  {
    if (m_bLooped)
    {
      curWaypoint = m_WayPoints.begin(); 
    }
  }
}  



#endif