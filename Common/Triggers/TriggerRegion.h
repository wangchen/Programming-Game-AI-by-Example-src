#ifndef TRIGGER_REGION_H
#define TRIGGER_REGION_H
//-----------------------------------------------------------------------------
//
//  Name:   TriggerRegion.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to define a region of influence for a trigger. A 
//          TriggerRegion has one method, isTouching, which returns true if
//          a given position is inside the region
//-----------------------------------------------------------------------------
#include "2d/Vector2d.h"
#include "2d/InvertedAABBox2D.h"

class TriggerRegion
{
public:

  virtual ~TriggerRegion(){}

  //returns true if an entity of the given size and position is intersecting
  //the trigger region.
  virtual bool isTouching(Vector2D EntityPos, double EntityRadius)const = 0;
};


//--------------------------- TriggerRegion_Circle ----------------------------
//
//  class to define a circular region of influence
//-----------------------------------------------------------------------------
class TriggerRegion_Circle : public TriggerRegion
{
private:

  //the center of the region
  Vector2D m_vPos;
  
  //the radius of the region
  double    m_dRadius;

public:

  TriggerRegion_Circle(Vector2D pos, 
                       double    radius):m_dRadius(radius),
                                        m_vPos(pos)
  {}

  bool isTouching(Vector2D pos, double EntityRadius)const
  {
    return Vec2DDistanceSq(m_vPos, pos) < (EntityRadius + m_dRadius)*(EntityRadius + m_dRadius);
  }
};


//--------------------------- TriggerRegion_Rectangle -------------------------
//
//  class to define a circular region of influence
//-----------------------------------------------------------------------------
class TriggerRegion_Rectangle : public TriggerRegion
{
private:

  InvertedAABBox2D* m_pTrigger;
  
public:

  TriggerRegion_Rectangle(Vector2D TopLeft, 
                          Vector2D BottomRight)
  {
    m_pTrigger = new InvertedAABBox2D(TopLeft, BottomRight);
  }

  ~TriggerRegion_Rectangle(){delete m_pTrigger;}

  //there's no need to do an accurate (and expensive) circle v
  //rectangle intersection test. Instead we'll just test the bounding box of
  //the given circle with the rectangle.
  bool isTouching(Vector2D pos, double EntityRadius)const
  {
    InvertedAABBox2D Box(Vector2D(pos.x-EntityRadius, pos.y-EntityRadius),
                         Vector2D(pos.x+EntityRadius, pos.y+EntityRadius));

    return Box.isOverlappedWith(*m_pTrigger);
  }
};


#endif