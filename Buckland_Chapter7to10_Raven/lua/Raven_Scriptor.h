#ifndef RAVEN_SCRIPTOR_H
#define RAVEN_SCRIPTOR_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Scriptor
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   A Singleton Scriptor class for use with the Raven project
//-----------------------------------------------------------------------------
#include "Script/scriptor.h"



#define script Raven_Scriptor::Instance()

class Raven_Scriptor : public Scriptor
{
private:
  
  Raven_Scriptor();

  //copy ctor and assignment should be private
  Raven_Scriptor(const Raven_Scriptor&);
  Raven_Scriptor& operator=(const Raven_Scriptor&);

public:

  static Raven_Scriptor* Instance();

};

#endif

 
  

