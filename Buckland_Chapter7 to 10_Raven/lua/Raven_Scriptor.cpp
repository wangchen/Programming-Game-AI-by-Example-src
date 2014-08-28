#include "Raven_Scriptor.h"

Raven_Scriptor* Raven_Scriptor::Instance()
{
  static Raven_Scriptor instance;

  return &instance;
}



Raven_Scriptor::Raven_Scriptor():Scriptor()
{
  RunScriptFile("Params.lua");
}