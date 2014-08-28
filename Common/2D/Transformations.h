#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
//------------------------------------------------------------------------
//
//  Name:   Transformations.h
//
//  Desc:   Functions for converting 2D vectors between World and Local
//          space.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>

#include "Vector2D.h"
#include "C2DMatrix.h"
#include "Transformations.h"






//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position, orientation and scale,
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------
inline std::vector<Vector2D> WorldTransform(std::vector<Vector2D> &points,
                                            const Vector2D   &pos,
                                            const Vector2D   &forward,
                                            const Vector2D   &side,
                                            const Vector2D   &scale)
{
	//copy the original vertices into the buffer about to be transformed
  std::vector<Vector2D> TranVector2Ds = points;
  
  //create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
  if ( (scale.x != 1.0) || (scale.y != 1.0) )
  {
	  matTransform.Scale(scale.x, scale.y);
  }

	//rotate
	matTransform.Rotate(forward, side);

	//and translate
	matTransform.Translate(pos.x, pos.y);
	
  //now transform the object's vertices
  matTransform.TransformVector2Ds(TranVector2Ds);

  return TranVector2Ds;
}

//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position and  orientation
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------
inline std::vector<Vector2D> WorldTransform(std::vector<Vector2D> &points,
                                 const Vector2D   &pos,
                                 const Vector2D   &forward,
                                 const Vector2D   &side)
{
	//copy the original vertices into the buffer about to be transformed
  std::vector<Vector2D> TranVector2Ds = points;
  
  //create a transformation matrix
	C2DMatrix matTransform;

	//rotate
	matTransform.Rotate(forward, side);

	//and translate
	matTransform.Translate(pos.x, pos.y);
	
  //now transform the object's vertices
  matTransform.TransformVector2Ds(TranVector2Ds);

  return TranVector2Ds;
}

//--------------------- PointToWorldSpace --------------------------------
//
//  Transforms a point from the agent's local space into world space
//------------------------------------------------------------------------
inline Vector2D PointToWorldSpace(const Vector2D &point,
                                    const Vector2D &AgentHeading,
                                    const Vector2D &AgentSide,
                                    const Vector2D &AgentPosition)
{
	//make a copy of the point
  Vector2D TransPoint = point;
  
  //create a transformation matrix
	C2DMatrix matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

	//and translate
	matTransform.Translate(AgentPosition.x, AgentPosition.y);
	
  //now transform the vertices
  matTransform.TransformVector2Ds(TransPoint);

  return TransPoint;
}

//--------------------- VectorToWorldSpace --------------------------------
//
//  Transforms a vector from the agent's local space into world space
//------------------------------------------------------------------------
inline Vector2D VectorToWorldSpace(const Vector2D &vec,
                                     const Vector2D &AgentHeading,
                                     const Vector2D &AgentSide)
{
	//make a copy of the point
  Vector2D TransVec = vec;
  
  //create a transformation matrix
	C2DMatrix matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

  //now transform the vertices
  matTransform.TransformVector2Ds(TransVec);

  return TransVec;
}


//--------------------- PointToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
inline Vector2D PointToLocalSpace(const Vector2D &point,
                             Vector2D &AgentHeading,
                             Vector2D &AgentSide,
                              Vector2D &AgentPosition)
{

	//make a copy of the point
  Vector2D TransPoint = point;
  
  //create a transformation matrix
	C2DMatrix matTransform;

  double Tx = -AgentPosition.Dot(AgentHeading);
  double Ty = -AgentPosition.Dot(AgentSide);

  //create the transformation matrix
  matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
  matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
  matTransform._31(Tx);           matTransform._32(Ty);
	
  //now transform the vertices
  matTransform.TransformVector2Ds(TransPoint);

  return TransPoint;
}

//--------------------- VectorToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
inline Vector2D VectorToLocalSpace(const Vector2D &vec,
                             const Vector2D &AgentHeading,
                             const Vector2D &AgentSide)
{ 

	//make a copy of the point
  Vector2D TransPoint = vec;
  
  //create a transformation matrix
	C2DMatrix matTransform;

  //create the transformation matrix
  matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
  matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
	
  //now transform the vertices
  matTransform.TransformVector2Ds(TransPoint);

  return TransPoint;
}

//-------------------------- Vec2DRotateAroundOrigin --------------------------
//
//  rotates a vector ang rads around the origin
//-----------------------------------------------------------------------------
inline void Vec2DRotateAroundOrigin(Vector2D& v, double ang)
{
  //create a transformation matrix
  C2DMatrix mat;

  //rotate
  mat.Rotate(ang);
	
  //now transform the object's vertices
  mat.TransformVector2Ds(v);
}

//------------------------ CreateWhiskers ------------------------------------
//
//  given an origin, a facing direction, a 'field of view' describing the 
//  limit of the outer whiskers, a whisker length and the number of whiskers
//  this method returns a vector containing the end positions of a series
//  of whiskers radiating away from the origin and with equal distance between
//  them. (like the spokes of a wheel clipped to a specific segment size)
//----------------------------------------------------------------------------
inline std::vector<Vector2D> CreateWhiskers(unsigned int  NumWhiskers,
                                            double        WhiskerLength,
                                            double        fov,
                                            Vector2D      facing,
                                            Vector2D      origin)
{
  //this is the magnitude of the angle separating each whisker
  double SectorSize = fov/(double)(NumWhiskers-1);

  std::vector<Vector2D> whiskers;
  Vector2D temp;
  double angle = -fov*0.5; 

  for (unsigned int w=0; w<NumWhiskers; ++w)
  {
    //create the whisker extending outwards at this angle
    temp = facing;
    Vec2DRotateAroundOrigin(temp, angle);
    whiskers.push_back(origin + WhiskerLength * temp);

    angle+=SectorSize;
  }

  return whiskers;
}


#endif