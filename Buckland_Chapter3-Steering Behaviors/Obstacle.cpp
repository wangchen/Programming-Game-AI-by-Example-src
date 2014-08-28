#include "Obstacle.h"
#include <fstream>


void Obstacle::Write(std::ostream& os)const
{
  os << std::endl;
  os << EntityType() << ",";
  os << Pos() << ",";
  os << BRadius();
}

void Obstacle::Read(std::ifstream& in)
{
  double x, y, r;

  in >> x >> y >> r;

  SetPos(Vector2D(x,y));
  
  SetBRadius(r);
}