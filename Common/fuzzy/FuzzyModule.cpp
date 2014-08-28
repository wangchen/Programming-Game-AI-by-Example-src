#pragma warning (disable:4786)
#include <stdarg.h>
#include <iostream>
#include <cassert>

#include "Fuzzy/FuzzyModule.h"

//------------------------------ dtor -----------------------------------------
FuzzyModule::~FuzzyModule()
{
  VarMap::iterator curVar = m_Variables.begin();
  for (curVar; curVar != m_Variables.end(); ++curVar)
  {
    delete curVar->second;
  }

  std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
  for (curRule; curRule != m_Rules.end(); ++curRule)
  {
    delete *curRule;
  }
}

//----------------------------- AddRule ---------------------------------------
void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
  m_Rules.push_back(new FuzzyRule(antecedent, consequence));
}

 
//-------------------------- CreateFLV ---------------------------
//
//  creates a new fuzzy variable and returns a reference to it
//-----------------------------------------------------------------------------
FuzzyVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
  m_Variables[VarName] = new FuzzyVariable();;

  return *m_Variables[VarName];
}


//---------------------------- WriteAllDOMs -----------------------------------
std::ostream& FuzzyModule::WriteAllDOMs(std::ostream& os)
{
  os << "\n\n";
  
  VarMap::iterator curVar = m_Variables.begin();
  for (curVar; curVar != m_Variables.end(); ++curVar)
  {
    os << "\n--------------------------- " << curVar->first;;
    curVar->second->WriteDOMs(os);

    os << std::endl;
  }

  return os;
}

