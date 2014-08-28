#ifndef FUZZY_RULE_H
#define FUZZY_RULE_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyRule.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   This class implements a fuzzy rule of the form:
//  
//          IF fzVar1 AND fzVar2 AND ... fzVarn THEN fzVar.c
//
//          
//-----------------------------------------------------------------------------
#include <vector>
#include "Fuzzy/FuzzySet.h"
#include "fuzzy/FuzzyOperators.h"
#include "misc/utils.h"


class FuzzyRule
{ 
private:

  //antecedent (usually a composite of several fuzzy sets and operators)
  const FuzzyTerm*  m_pAntecedent;

  //consequence (usually a single fuzzy set, but can be several ANDed together)
  FuzzyTerm*        m_pConsequence;

  //it doesn't make sense to allow clients to copy rules
  FuzzyRule(const FuzzyRule&);
  FuzzyRule& operator=(const FuzzyRule&);


public:

  FuzzyRule(const FuzzyTerm& ant,
            const FuzzyTerm& con):m_pAntecedent(ant.Clone()),
                                  m_pConsequence(con.Clone())
  {}

  ~FuzzyRule(){delete m_pAntecedent; delete m_pConsequence;}

  void SetConfidenceOfConsequentToZero(){m_pConsequence->ClearDOM();}

  //this method updates the DOM (the confidence) of the consequent term with
  //the DOM of the antecedent term. 
  void Calculate()
  {
    m_pConsequence->ORwithDOM(m_pAntecedent->GetDOM());
  }
};

#endif