#include "fuzzy/fuzzyvariable.h"
#include "fuzzy/fuzzyoperators.h"
#include "fuzzy/FuzzySet_triangle.h"
#include "fuzzy/FuzzySet_LeftShoulder.h"
#include "fuzzy/FuzzySet_RightShoulder.h"
#include "fuzzy/FuzzySet_Singleton.h"
#include "fuzzy/FzSet.h"
#include "misc/utils.h"
#include <cassert>
#include <iostream>
#include <algorithm>

//------------------------------ dtor -----------------------------------------
//-----------------------------------------------------------------------------
FuzzyVariable::~FuzzyVariable()
{
  MemberSets::iterator it;
  for (it = m_MemberSets.begin(); it != m_MemberSets.end(); ++it)
  {
    delete it->second;
  }
}

//--------------------------- Fuzzify -----------------------------------------
//
//  takes a crisp value and calculates its degree of membership for each set
//  in the variable.
//-----------------------------------------------------------------------------
void FuzzyVariable::Fuzzify(double val)
{    
  //make sure the value is within the bounds of this variable
  assert ( (val >= m_dMinRange) && (val <= m_dMaxRange) && 
           "<FuzzyVariable::Fuzzify>: value out of range");

  //for each set in the flv calculate the DOM for the given value
  MemberSets::const_iterator curSet;
  for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
  {
    curSet->second->SetDOM(curSet->second->CalculateDOM(val));
  }
}


//--------------------------- DeFuzzifyMaxAv ----------------------------------
//
// defuzzifies the value by averaging the maxima of the sets that have fired
//
// OUTPUT = sum (maxima * DOM) / sum (DOMs) 
//-----------------------------------------------------------------------------
double FuzzyVariable::DeFuzzifyMaxAv()const
{
  double bottom = 0.0;
  double top    = 0.0;

  MemberSets::const_iterator curSet;
  for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
  {
    bottom += curSet->second->GetDOM();

    top += curSet->second->GetRepresentativeVal() * curSet->second->GetDOM();
  }

  //make sure bottom is not equal to zero
  if (isEqual(0, bottom)) return 0.0;

  return top / bottom;   
}

//------------------------- DeFuzzifyCentroid ---------------------------------
//
//  defuzzify the variable using the centroid method
//-----------------------------------------------------------------------------
double FuzzyVariable::DeFuzzifyCentroid(int NumSamples)const
{
  //calculate the step size
  double StepSize = (m_dMaxRange - m_dMinRange)/(double)NumSamples;

  double TotalArea    = 0.0;
  double SumOfMoments = 0.0;

  //step through the range of this variable in increments equal to StepSize
  //adding up the contribution (lower of CalculateDOM or the actual DOM of this
  //variable's fuzzified value) for each subset. This gives an approximation of
  //the total area of the fuzzy manifold.(This is similar to how the area under
  //a curve is calculated using calculus... the heights of lots of 'slices' are
  //summed to give the total area.)
  //
  //in addition the moment of each slice is calculated and summed. Dividing
  //the total area by the sum of the moments gives the centroid. (Just like
  //calculating the center of mass of an object)
  for (int samp=1; samp<=NumSamples; ++samp)
  {
    //for each set get the contribution to the area. This is the lower of the 
    //value returned from CalculateDOM or the actual DOM of the fuzzified 
    //value itself   
    MemberSets::const_iterator curSet = m_MemberSets.begin();
    for (curSet; curSet != m_MemberSets.end(); ++curSet)
    {
      double contribution = 
          MinOf(curSet->second->CalculateDOM(m_dMinRange + samp * StepSize),
                curSet->second->GetDOM());

      TotalArea += contribution;

      SumOfMoments += (m_dMinRange + samp * StepSize)  * contribution;
    }
  }

  //make sure total area is not equal to zero
  if (isEqual(0, TotalArea)) return 0.0;
  
  return (SumOfMoments / TotalArea);
}

//------------------------- AddTriangularSet ----------------------------------
//
//  adds a triangular shaped fuzzy set to the variable
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddTriangularSet(std::string name,
                                     double       minBound,
                                     double       peak,
                                     double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_Triangle(peak,
                                             peak-minBound,
                                             maxBound-peak);
  //adjust range if necessary
  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}

//--------------------------- AddLeftShoulder ---------------------------------
//
//  adds a left shoulder type set
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddLeftShoulderSet(std::string name,
                                        double       minBound,
                                        double       peak,
                                        double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_LeftShoulder(peak, peak-minBound, maxBound-peak);

  //adjust range if necessary
  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}


//--------------------------- AddRightShoulder ---------------------------------
//
//  adds a left shoulder type set
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddRightShoulderSet(std::string name,
                                         double       minBound,
                                         double       peak,
                                         double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_RightShoulder(peak, peak-minBound, maxBound-peak);

  //adjust range if necessary
  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}


//--------------------------- AddSingletonSet ---------------------------------
//
//  adds a singleton to the variable
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddSingletonSet(std::string name,
                                    double       minBound,
                                    double       peak,
                                    double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_Singleton(peak,
                                              peak-minBound,
                                              maxBound-peak);

  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}

//---------------------------- AdjustRangeToFit -------------------------------
//
//  this method is called with the upper and lower bound of a set each time a
//  new set is added to adjust the upper and lower range values accordingly
//-----------------------------------------------------------------------------
void FuzzyVariable::AdjustRangeToFit(double minBound, double maxBound)
{
  if (minBound < m_dMinRange) m_dMinRange = minBound;
  if (maxBound > m_dMaxRange) m_dMaxRange = maxBound;
}

//---------------------------- WriteDOMs --------------------------------------
std::ostream& FuzzyVariable::WriteDOMs(std::ostream& os)
{
  MemberSets::iterator it;
  for (it = m_MemberSets.begin(); it != m_MemberSets.end(); ++it)
  {

    os << "\n" << it->first << " is " << it->second->GetDOM();
  }

  os << "\nMin Range: " << m_dMinRange << "\nMax Range: " << m_dMaxRange;

    return os;
  
}