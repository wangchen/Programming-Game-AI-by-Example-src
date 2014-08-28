#include "FuzzySet_RightShoulder.h"
#include <cassert>


double FuzzySet_RightShoulder::CalculateDOM(double val)const
{
  //test for the case where the left or right offsets are zero
  //(to prevent divide by zero errors below)
  if ( (isEqual(m_dRightOffset, 0.0) && (isEqual(m_dPeakPoint, val))) ||
       (isEqual(m_dLeftOffset, 0.0) && (isEqual(m_dPeakPoint, val))) )
  {
    return 1.0;
  }
  
  //find DOM if left of center
  else if ( (val <= m_dPeakPoint) && (val > (m_dPeakPoint - m_dLeftOffset)) )
  {
    double grad = 1.0 / m_dLeftOffset;

    return grad * (val - (m_dPeakPoint - m_dLeftOffset));
  }
  //find DOM if right of center and less than center + right offset
  else if ( (val > m_dPeakPoint) && (val <= m_dPeakPoint+m_dRightOffset) )
  {
    return 1.0;
  }

  else
  {
    return 0;
  }
}