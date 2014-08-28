#ifndef FUZZYSET_TRIANGLE_H
#define FUZZYSET_TRIANGLE_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySetTriangle.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   This is a simple class to define fuzzy sets that have a triangular 
//          shape and can be defined by a mid point, a left displacement and a
//          right displacement. 
//-----------------------------------------------------------------------------
#include "fuzzy/FuzzySet.h"
#include "utils.h"



class FuzzySet_Triangle : public FuzzySet
{
private:

  //the values that define the shape of this FLV
  double   m_dMidPoint;
  double   m_dLeftOffset;
  double   m_dRightOffset;

public:
  
  FuzzySet_Triangle(std::string name,
                double mid,
                double lft,
                double rgt):FuzzySet(name),
                           m_dMidPoint(mid),
                           m_dLeftOffset(lft),
                           m_dRightOffset(rgt)
  {}

  //this method calculates the degree of membership for a particular value
  inline double CalculateDOM(double val);

  //for a triangular set this is the range value at the midpoint
  double RepresentativeValue()const{return m_dMidPoint;}
  
};

///////////////////////////////////////////////////////////////////////////////

inline
double FuzzySet_Triangle::CalculateDOM(double val)
{
  //test for the case where the triangle's left or right offsets are zero
  if ( (isEqual(m_dRightOffset, 0.0) && (isEqual(m_dMidPoint, val))) ||
       (isEqual(m_dLeftOffset, 0.0) && (isEqual(m_dMidPoint, val))) )
  {
    return 1.0;
  }

  //find DOM if left of center
  if ( (val <= m_dMidPoint) && (val > (m_dMidPoint - m_dLeftOffset)) )
  {
    double grad = 1.0 / m_dLeftOffset;

    return grad * (val - (m_dMidPoint - m_dLeftOffset));
  }
  //find DOM if right of center
  else if ( (val > m_dMidPoint) && (val < (m_dMidPoint + m_dRightOffset)) )
  {
    double grad = 1.0 / -m_dRightOffset;

    return grad * (val - m_dMidPoint) + 1.0;
  }
  //out of range of this FLV, return zero
  else
  {
    return 0.0;
  }

}

#endif