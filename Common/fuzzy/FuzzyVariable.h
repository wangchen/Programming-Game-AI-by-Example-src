#ifndef FLV_H
#define FLV_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyVariable.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Class to define a fuzzy linguistic variable (FLV).
//
//          An FLV comprises of a number of fuzzy sets  
//
//-----------------------------------------------------------------------------
#include <map>
#include <iosfwd>
#include <string>

class FuzzySet;
class FzSet;
class FuzzyModule;


class FuzzyVariable
{
private:
  
  typedef std::map<std::string, FuzzySet*>  MemberSets;
    
private:
  
  //disallow copies
  FuzzyVariable(const FuzzyVariable&);
  FuzzyVariable& operator=(const FuzzyVariable&);

private:
 
  //a map of the fuzzy sets that comprise this variable
  MemberSets   m_MemberSets;

  //the minimum and maximum value of the range of this variable
  double        m_dMinRange;
  double        m_dMaxRange;
  

  //this method is called with the upper and lower bound of a set each time a
  //new set is added to adjust the upper and lower range values accordingly
  void AdjustRangeToFit(double min, double max);

  //a client retrieves a reference to a fuzzy variable when an instance is
  //created via FuzzyModule::CreateFLV(). To prevent the client from deleting
  //the instance the FuzzyVariable destructor is made private and the 
  //FuzzyModule class made a friend.
  ~FuzzyVariable();

  friend class FuzzyModule;


public:

  FuzzyVariable():m_dMinRange(0.0),m_dMaxRange(0.0){}
  
  //the following methods create instances of the sets named in the method
  //name and add them to the member set map. Each time a set of any type is
  //added the m_dMinRange and m_dMaxRange are adjusted accordingly. All of the
  //methods return a proxy class representing the newly created instance. This
  //proxy set can be used as an operand when creating the rule base.
  FzSet  AddLeftShoulderSet(std::string name, double minBound, double peak, double maxBound);

  FzSet  AddRightShoulderSet(std::string name, double minBound, double peak, double maxBound);

  FzSet  AddTriangularSet(std::string name,
                             double       minBound,
                             double       peak,
                             double       maxBound);

  FzSet  AddSingletonSet(std::string name,
                            double       minBound,
                            double       peak,
                            double       maxBound);
  
  
  //fuzzify a value by calculating its DOM in each of this variable's subsets
  void        Fuzzify(double val);

  //defuzzify the variable using the max average method
  double       DeFuzzifyMaxAv()const;

  //defuzzify the variable using the centroid method
  double       DeFuzzifyCentroid(int NumSamples)const;



  std::ostream& WriteDOMs(std::ostream& os);
};




          
#endif