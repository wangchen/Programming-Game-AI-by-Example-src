#include "FuzzySet_Singleton.h"

double FuzzySet_Singleton::CalculateDOM(double val)const
{
  if ( (val >= m_dMidPoint-m_dLeftOffset) &&
       (val <= m_dMidPoint+m_dRightOffset) )
  {
    return 1.0;
  }

  //out of range of this FLV, return zero
  else
  {
    return 0.0;
  }
}