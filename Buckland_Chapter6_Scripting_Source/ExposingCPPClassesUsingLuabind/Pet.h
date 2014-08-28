#ifndef PET_H
#define PET_H


#include <string>
#include <iostream>
#include "Animal.h"



class Pet : public Animal
{
private:
  
  std::string  m_Name;

public:

  Pet(std::string name,
      std::string noise,
      int         NumLegs):Animal(noise, NumLegs),
                           m_Name(name)
  {}

  std::string GetName()const{return m_Name;}  
};





#endif 