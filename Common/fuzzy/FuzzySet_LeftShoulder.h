#ifndef FUZZYSET_LEFTSHOULDER_H
#define FUZZYSET_LEFTSHOULDER_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySet_LeftShoulder.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   definition of a fuzzy set that has a left shoulder shape. (the
//          minimum value this variable can accept is *any* value less than the
//          midpoint.
//-----------------------------------------------------------------------------
#include "fuzzy/FuzzySet.h"
#include "misc/utils.h"



class FuzzySet_LeftShoulder : public FuzzySet
{
private:

  //the values that define the shape of this FLV
  double   m_dPeakPoint;
  double   m_dRightOffset;
  double   m_dLeftOffset;

public:
  
  FuzzySet_LeftShoulder(double peak,
                        double LeftOffset,
                        double RightOffset):  
  
                  FuzzySet( ((peak - LeftOffset) + peak) / 2),
                  m_dPeakPoint(peak),
                  m_dLeftOffset(LeftOffset),
                  m_dRightOffset(RightOffset)
  {}

  //this method calculates the degree of membership for a particular value
  double CalculateDOM(double val)const;  
};



#endif