#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>



class Animal
{
private:
  
  int          m_iNumLegs;

  std::string  m_NoiseEmitted;

public:

  Animal(std::string NoiseEmitted,
         int         NumLegs):m_iNumLegs(NumLegs),
                              m_NoiseEmitted(NoiseEmitted)
  {}

  virtual ~Animal(){}

  virtual void Speak()const
  {std::cout << "\n[C++]: " << m_NoiseEmitted << std::endl;}

  int          NumLegs()const{return m_iNumLegs;}
                                 
};




#endif