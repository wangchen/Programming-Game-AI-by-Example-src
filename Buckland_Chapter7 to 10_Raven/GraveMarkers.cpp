#include "GraveMarkers.h"
#include "misc/cgdi.h"
#include "2D/Transformations.h"

//------------------------------- ctor ----------------------------------------
//-----------------------------------------------------------------------------
GraveMarkers::GraveMarkers(double lifetime):m_dLifeTime(lifetime)
{
      //create the vertex buffer for the graves
    const int NumripVerts = 9;
    const Vector2D rip[NumripVerts] = {Vector2D(-4, -5),
                                       Vector2D(-4, 3),
                                       Vector2D(-3, 5),
                                       Vector2D(-1, 6),
                                       Vector2D(1, 6),
                                       Vector2D(3, 5),
                                       Vector2D(4, 3),
                                       Vector2D(4, -5),
                                       Vector2D(-4, -5)};
  for (int i=0; i<NumripVerts; ++i)
  {
    m_vecRIPVB.push_back(rip[i]);
  }
}


void GraveMarkers::Update()
{
  GraveList::iterator it = m_GraveList.begin();
  while (it != m_GraveList.end())
  {
    if (Clock->GetCurrentTime() - it->TimeCreated > m_dLifeTime)
    {
      it = m_GraveList.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
    

void GraveMarkers::Render()
{
  GraveList::iterator it = m_GraveList.begin();
  Vector2D facing(-1,0);
  for (it; it != m_GraveList.end(); ++it)
  {
    
    m_vecRIPVBTrans = WorldTransform(m_vecRIPVB,
                                   it->Position,
                                   facing,
                                   facing.Perp(),
                                   Vector2D(1,1));

    gdi->BrownPen();
    gdi->ClosedShape(m_vecRIPVBTrans);
    gdi->TextColor(133,90,0);
    gdi->TextAtPos(it->Position.x - 10, it->Position.y - 5, "RIP");
  }
}

void GraveMarkers::AddGrave(Vector2D pos)
{
  m_GraveList.push_back(GraveRecord(pos));
}