#include "Raven_Door.h"
#include "Messaging/telegram.h"
#include "misc/Stream_Utility_Functions.h"
#include <algorithm>
#include "Raven_Messages.h"
#include "Raven_Map.h"
#include "2d/wall2d.h"

//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Raven_Door::Raven_Door(Raven_Map* pMap,
                       std::ifstream& is):

                                  BaseGameEntity(GetValueFromStream<int>(is)),
                                  m_Status(closed),
                                  m_iNumTicksStayOpen(60)                   //MGC!
{
  Read(is);

  m_vtoP2Norm =  Vec2DNormalize(m_vP2 - m_vP1);
  m_dCurrentSize = m_dSize = Vec2DDistance(m_vP2, m_vP1);

  Vector2D perp = m_vtoP2Norm.Perp();
  
  //create the walls that make up the door's geometry
  m_pWall1 = pMap->AddWall(m_vP1+perp, m_vP2+perp);
  m_pWall2 = pMap->AddWall(m_vP2-perp, m_vP1-perp);
}

//---------------------------- dtor -------------------------------------------
//-----------------------------------------------------------------------------
Raven_Door::~Raven_Door()
{
}


//--------------------------- Update ------------------------------------------
void Raven_Door::Update()
{
  switch (m_Status)
  {
  case opening:

      Open(); break;

  case closing:

      Close(); break;

  case open:
    {
      if (m_iNumTicksCurrentlyOpen-- < 0)
      {
        m_Status = closing;
      }
    }
  }


}

//---------------------------- ChangePosition ---------------------------------
void Raven_Door::ChangePosition(Vector2D newP1, Vector2D newP2)
{
  m_vP1 = newP1;
  m_vP2 = newP2;

  m_pWall1->SetFrom(m_vP1 + m_vtoP2Norm.Perp());
  m_pWall1->SetTo(m_vP2 + m_vtoP2Norm.Perp());

  m_pWall2->SetFrom(m_vP2 - m_vtoP2Norm.Perp());
  m_pWall2->SetTo(m_vP1 - m_vtoP2Norm.Perp());
}

//---------------------------- Open -------------------------------------------
void Raven_Door::Open()
{
  if (m_Status == opening)
  {
    if (m_dCurrentSize < 2)
    {
      m_Status = open;

      m_iNumTicksCurrentlyOpen = m_iNumTicksStayOpen;

      return;
      
    }

    //reduce the current size
    m_dCurrentSize -= 1;

    Clamp(m_dCurrentSize, 0, m_dSize);

    ChangePosition(m_vP1, m_vP1 + m_vtoP2Norm * m_dCurrentSize);

  }
}

//------------------------------- Close ---------------------------------------
//-----------------------------------------------------------------------------
void Raven_Door::Close()
{
  if (m_Status == closing)
  {
    if (m_dCurrentSize == m_dSize)
    {
      m_Status = closed;
      return;
      
    }

    //reduce the current size
    m_dCurrentSize += 1;

    Clamp(m_dCurrentSize, 0, m_dSize);

    ChangePosition(m_vP1, m_vP1 + m_vtoP2Norm * m_dCurrentSize);

  }
}

//-------------------------- AddSwitch ----------------------------------------
//
//  adds the id of a trigger for the door to notify when operating
//-----------------------------------------------------------------------------
void Raven_Door::AddSwitch(unsigned int id)
{
  //only add the trigger if it isn't already present
  if (std::find(m_Switches.begin(),
                m_Switches.end(),
                id) != m_Switches.end())
  {
    m_Switches.push_back(id);
  }
}


//----------------------------- Read -----------------------------------------
//-----------------------------------------------------------------------------
void Raven_Door::Read(std::ifstream&  os)
{
  double x, y;

  //grab the hinge points
  os >> x >> y;
  m_vP1 = Vector2D(x,y);
  os >> x >> y;
  m_vP2 = Vector2D(x,y);

  //grab the number of triggers
  int num, trig;

  os >> num;

  //save the trigger IDs
  for (int i=0; i<num; ++i)
  {
    os >> trig;

    m_Switches.push_back(trig);
  }
}

//------------------------------- HandleMessage -------------------------------
//-----------------------------------------------------------------------------
bool Raven_Door::HandleMessage(const Telegram& msg)
{
  if (msg.Msg == Msg_OpenSesame)
  {
    if (m_Status != open)
    {
      m_Status = opening;
    }

    return true;
  }

  return false;
}


//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void Raven_Door::Render()
{
  gdi->ThickBluePen();
  gdi->Line(m_vP1, m_vP2); 
}


