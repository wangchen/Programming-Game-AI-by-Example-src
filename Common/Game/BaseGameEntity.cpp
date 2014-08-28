#include "BaseGameEntity.h"


int BaseGameEntity::m_iNextValidID = 0;

//------------------------------ ctor -----------------------------------------
//-----------------------------------------------------------------------------
BaseGameEntity::BaseGameEntity(int ID):m_dBoundingRadius(0.0),
                                       m_vScale(Vector2D(1.0,1.0)),
                                       m_iType(default_entity_type),
                                       m_bTag(false)
{
  SetID(ID);
}

//----------------------------- SetID -----------------------------------------
//
//  this must be called within each constructor to make sure the ID is set
//  correctly. It verifies that the value passed to the method is greater
//  or equal to the next valid ID, before setting the ID and incrementing
//  the next valid ID
//-----------------------------------------------------------------------------
void BaseGameEntity::SetID(int val)
{
  //make sure the val is equal to or greater than the next available ID
  assert ( (val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

  m_ID = val;
    
  m_iNextValidID = m_ID + 1;
}
