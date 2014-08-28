#include "Goal_MoveToItem.h"

#include "..\Raven_Bot.h"
#include "..\Raven_NavModule.h"

#include "Raven_GoalQ.h"



void Goal_MoveToItem::Initialize()
{
  //request a path to the item
  m_pOwner->NavModule()->CreatePathToItem(m_iItemType);

  //the bot may have to wait a few update cycles before a path is calculated
  //so for appearances sake it just moves forward a little
  m_pOwner->GoalQ()->AddGoal_SeekToPosition(m_pOwner->Pos() + m_pOwner->Facing()*20);

  //this goal is now satisfied
  m_bSatisfied = true;
}
