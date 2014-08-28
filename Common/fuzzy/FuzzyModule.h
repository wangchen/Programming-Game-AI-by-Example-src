#ifndef FUZZY_MODULE_H
#define FUZZY_MODULE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyModule.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   this class describes a fuzzy module: a collection of fuzzy variables
//          and the rules that operate on them.
//
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <map>
#include <iosfwd>

#include "FuzzySet.h"
#include "FuzzyVariable.h"
#include "FuzzyRule.h"
#include "FuzzyOperators.h"
#include "FzSet.h"
#include "FuzzyHedges.h"



class FuzzyModule
{
private:

  typedef std::map<std::string, FuzzyVariable*> VarMap;
  
public:

  //you must pass one of these values to the defuzzify method. This module
  //only supports the MaxAv and centroid methods.
  enum DefuzzifyMethod{max_av, centroid};

  //when calculating the centroid of the fuzzy manifold this value is used
  //to determine how many cross-sections should be sampled
  enum {NumSamples = 15};

private:

  //a map of all the fuzzy variables this module uses
  VarMap                   m_Variables;

  //a vector containing all the fuzzy rules
  std::vector<FuzzyRule*>   m_Rules;
 

  //zeros the DOMs of the consequents of each rule. Used by Defuzzify()
  inline void SetConfidencesOfConsequentsToZero();


public:

  ~FuzzyModule();

  //creates a new 'empty' fuzzy variable and returns a reference to it.
  FuzzyVariable&  CreateFLV(const std::string& VarName);
  
  //adds a rule to the module
  void            AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence);

  //this method calls the Fuzzify method of the named FLV 
  inline void     Fuzzify(const std::string& NameOfFLV, double val);

  //given a fuzzy variable and a deffuzification method this returns a 
  //crisp value
  inline double    DeFuzzify(const std::string& key,
                            DefuzzifyMethod    method = max_av);
    
  
  //writes the DOMs of all the variables in the module to an output stream
  std::ostream&   WriteAllDOMs(std::ostream& os);

};

///////////////////////////////////////////////////////////////////////////////

//----------------------------- Fuzzify ---------------------------------------
//
//  this method calls the Fuzzify method of the variable with the same name
//  as the key
//-----------------------------------------------------------------------------
inline void FuzzyModule::Fuzzify(const std::string& NameOfFLV, double val)
{
  //first make sure the key exists
  assert ( (m_Variables.find(NameOfFLV) != m_Variables.end()) &&
          "<FuzzyModule::Fuzzify>:key not found");

  m_Variables[NameOfFLV]->Fuzzify(val);
}

//---------------------------- DeFuzzify --------------------------------------
//
//  given a fuzzy variable and a deffuzification method this returns a 
//  crisp value
//-----------------------------------------------------------------------------
inline double
FuzzyModule::DeFuzzify(const std::string& NameOfFLV, DefuzzifyMethod method)
{
  //first make sure the key exists
  assert ( (m_Variables.find(NameOfFLV) != m_Variables.end()) &&
          "<FuzzyModule::DeFuzzifyMaxAv>:key not found");

  //clear the DOMs of all the consequents of all the rules
  SetConfidencesOfConsequentsToZero();

  //process the rules
  std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
  for (curRule; curRule != m_Rules.end(); ++curRule)
  {
    (*curRule)->Calculate();
  }

  //now defuzzify the resultant conclusion using the specified method
  switch (method)
  {
  case centroid:

    return m_Variables[NameOfFLV]->DeFuzzifyCentroid(NumSamples);

    break;

  case max_av:

    return m_Variables[NameOfFLV]->DeFuzzifyMaxAv();

    break;
  }

  return 0;
}



//-------------------------- ClearConsequents ---------------------------------
//
//  zeros the DOMs of the consequents of each rule
//-----------------------------------------------------------------------------
inline void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
  std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
  for (curRule; curRule != m_Rules.end(); ++curRule)
  {
    (*curRule)->SetConfidenceOfConsequentToZero();
  }
}


#endif