#include "FuzzyOperators.h"
 
///////////////////////////////////////////////////////////////////////////////
//
//  implementation of FzAND
//
///////////////////////////////////////////////////////////////////////////////
FzAND::FzAND(const FzAND& fa)
{
   std::vector<FuzzyTerm*>::const_iterator curTerm;
   for (curTerm = fa.m_Terms.begin(); curTerm != fa.m_Terms.end(); ++curTerm)
   {
     m_Terms.push_back((*curTerm)->Clone());
   }
}
   
  //ctor using two terms
FzAND::FzAND(FuzzyTerm& op1, FuzzyTerm& op2)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
}

//ctor using three terms
FzAND::FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
   m_Terms.push_back(op3.Clone());
}

      //ctor using four terms
FzAND::FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
   m_Terms.push_back(op3.Clone());
   m_Terms.push_back(op4.Clone());
}


FzAND::~FzAND()
{
  std::vector<FuzzyTerm*>::iterator curTerm;
  for (curTerm = m_Terms.begin(); curTerm != m_Terms.end(); ++curTerm)
  {
    delete *curTerm;
  }
}
  

//--------------------------- GetDOM ------------------------------------------
//
//  the AND operator returns the minimum DOM of the sets it is operating on
//-----------------------------------------------------------------------------
double FzAND::GetDOM()const
{
  double smallest = MaxDouble;

  std::vector<FuzzyTerm*>::const_iterator curTerm;
  for (curTerm = m_Terms.begin(); curTerm != m_Terms.end(); ++curTerm)
  {
    if ((*curTerm)->GetDOM() < smallest)
    {
      smallest = (*curTerm)->GetDOM();
    }
  }

  return smallest;
}


//------------------------- ORwithDOM -----------------------------------------
void FzAND::ORwithDOM(double val)
{
  std::vector<FuzzyTerm*>::iterator curTerm;
  for (curTerm = m_Terms.begin(); curTerm != m_Terms.end(); ++curTerm)
  {
    (*curTerm)->ORwithDOM(val);
  }
}

//---------------------------- ClearDOM ---------------------------------------
void FzAND::ClearDOM()
{
  std::vector<FuzzyTerm*>::iterator curTerm;
  for (curTerm = m_Terms.begin(); curTerm != m_Terms.end(); ++curTerm)
  {
    (*curTerm)->ClearDOM();
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  implementation of FzOR
//
///////////////////////////////////////////////////////////////////////////////
FzOR::FzOR(const FzOR& fa)
{
   std::vector<FuzzyTerm*>::const_iterator curTerm;
   for (curTerm = fa.m_Terms.begin(); curTerm != fa.m_Terms.end(); ++curTerm)
   {
     m_Terms.push_back((*curTerm)->Clone());
   }
}
   
  //ctor using two terms
FzOR::FzOR(FuzzyTerm& op1, FuzzyTerm& op2)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
}

    //ctor using three terms
FzOR::FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
   m_Terms.push_back(op3.Clone());
}

      //ctor using four terms
FzOR::FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
   m_Terms.push_back(op3.Clone());
   m_Terms.push_back(op4.Clone());
}


FzOR::~FzOR()
{
  std::vector<FuzzyTerm*>::iterator curTerm;
  for (curTerm = m_Terms.begin(); curTerm != m_Terms.end(); ++curTerm)
  {
    delete *curTerm;
  }
}
  

//--------------------------- GetDOM ------------------------------------------
//
//  the OR operator returns the maximum DOM of the sets it is operating on
//----------------------------------------------------------------------------- 
double FzOR::GetDOM()const
{
  double largest = MinFloat;

  std::vector<FuzzyTerm*>::const_iterator curTerm;
  for (curTerm = m_Terms.begin(); curTerm != m_Terms.end(); ++curTerm)
  {
    if ((*curTerm)->GetDOM() > largest)
    {
      largest = (*curTerm)->GetDOM();
    }
  }

  return largest;
}
