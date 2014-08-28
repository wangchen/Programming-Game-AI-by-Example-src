#ifndef PROXY_FUZZY_SET
#define PROXY_FUZZY_SET
//-----------------------------------------------------------------------------
//
//  Name:   FzSet.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to provide a proxy for a fuzzy set. The proxy inherits from
//          FuzzyTerm and therefore can be used to create fuzzy rules
//-----------------------------------------------------------------------------
#include "FuzzyTerm.h"
#include "FuzzySet.h"

class FzAND;

class FzSet : public FuzzyTerm
{
private:
  
  //let the hedge classes be friends 
  friend class FzVery;
  friend class FzFairly;

private:

  //a reference to the fuzzy set this proxy represents
  FuzzySet& m_Set;

public:

  FzSet(FuzzySet& fs):m_Set(fs){}

  FuzzyTerm* Clone()const{return new FzSet(*this);}
  double     GetDOM()const {return m_Set.GetDOM();}
  void       ClearDOM(){m_Set.ClearDOM();}
  void       ORwithDOM(double val){m_Set.ORwithDOM(val);}
};


#endif

