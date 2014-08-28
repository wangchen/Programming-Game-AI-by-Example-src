#include "Trigger_WeaponGiver.h"
#include "misc/Cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include <fstream>
#include "../lua/Raven_Scriptor.h"
#include "../constants.h"
#include "../Raven_ObjectEnumerations.h"
#include "../Raven_WeaponSystem.h"


///////////////////////////////////////////////////////////////////////////////

Trigger_WeaponGiver::Trigger_WeaponGiver(std::ifstream& datafile):
      
          Trigger_Respawning<Raven_Bot>(GetValueFromStream<int>(datafile))
{
  Read(datafile);

  //create the vertex buffer for the rocket shape
  const int NumRocketVerts = 8;
  const Vector2D rip[NumRocketVerts] = {Vector2D(0, 3),
                                       Vector2D(1, 2),
                                       Vector2D(1, 0),
                                       Vector2D(2, -2),
                                       Vector2D(-2, -2),
                                       Vector2D(-1, 0),
                                       Vector2D(-1, 2),
                                       Vector2D(0, 3)};
  
  for (int i=0; i<NumRocketVerts; ++i)
  {
    m_vecRLVB.push_back(rip[i]);
  }
}


void Trigger_WeaponGiver::Try(Raven_Bot* pBot)
{
  if (this->isActive() && this->isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
  {
    pBot->GetWeaponSys()->AddWeapon(EntityType());

    Deactivate();
  } 
}




void Trigger_WeaponGiver::Read(std::ifstream& in)
{
  double x, y, r;
  int GraphNodeIndex;
  
  in >>  x >> y  >> r >> GraphNodeIndex;

  SetPos(Vector2D(x,y)); 
  SetBRadius(r);
  SetGraphNodeIndex(GraphNodeIndex);

  //create this trigger's region of fluence
  AddCircularTriggerRegion(Pos(), script->GetDouble("DefaultGiverTriggerRange"));


  SetRespawnDelay((unsigned int)(script->GetDouble("Weapon_RespawnDelay") * FrameRate));
}



void Trigger_WeaponGiver::Render()
{
  if (isActive())
  {
    switch (EntityType())
    {
      case type_rail_gun:
        {
          gdi->BluePen();
          gdi->BlueBrush();
          gdi->Circle(Pos(), 3);
          gdi->ThickBluePen();
          gdi->Line(Pos(), Vector2D(Pos().x, Pos().y-9));
        }

        break;

      case type_shotgun:
        {

          gdi->BlackBrush();
          gdi->BrownPen();
          const double sz = 3.0;
          gdi->Circle(Pos().x-sz,Pos().y, sz);
          gdi->Circle(Pos().x+sz,Pos().y, sz);
        }

        break;

      case type_rocket_launcher:
        {

           Vector2D facing(-1,0);

           m_vecRLVBTrans = WorldTransform(m_vecRLVB,
                                          Pos(),
                                          facing,
                                          facing.Perp(),
                                          Vector2D(2.5,2.5));

            gdi->RedPen();
            gdi->ClosedShape(m_vecRLVBTrans);
        }
      
        break;

    }//end switch
  }
}