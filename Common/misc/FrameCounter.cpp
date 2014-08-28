#include "framecounter.h"


FrameCounter* FrameCounter::Instance()
{
  static FrameCounter instance;

  return &instance;
}