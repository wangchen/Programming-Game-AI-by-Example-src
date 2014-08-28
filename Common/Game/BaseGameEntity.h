 #ifndef BASE_GAME_ENTITY_H
#define BASE_GAME_ENTITY_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name: BaseGameEntity.h
//
//  Desc: Base class to define a common interface for all game
//        entities
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>
#include <string>
#include <iosfwd>
#include "2D/Vector2D.h"
#include "2D/Geometry.h"
#include "misc/utils.h"



struct Telegram;


class BaseGameEntity
{
public:
  
  enum {default_entity_type = -1};

private:
  
  //each entity has a unique ID
  int         m_ID;

  //every entity has a type associated with it (health, troll, ammo etc)
  int         m_iType;

  //this is a generic flag. 
  bool        m_bTag;

  //this is the next valid ID. Each time a BaseGameEntity is instantiated
  //this value is updated
  static int  m_iNextValidID;

  //this must be called within each constructor to make sure the ID is set
  //correctly. It verifies that the value passed to the method is greater
  //or equal to the next valid ID, before setting the ID and incrementing
  //the next valid ID
  void SetID(int val);


protected:
  
  //its location in the environment
  Vector2D m_vPosition;

  Vector2D m_vScale;

  //the magnitude of this object's bounding radius
  double    m_dBoundingRadius;

  
  BaseGameEntity(int ID);

public:

  virtual ~BaseGameEntity(){}

  virtual void Update(){}; 

  virtual void Render()=0;
  
  virtual bool HandleMessage(const Telegram& msg){return false;}
  
  //entities should be able to read/write their data to a stream
  virtual void Write(std::ostream&  os)const{}
  virtual void Read (std::ifstream& is){}

  //use this to grab the next valid ID
  static int   GetNextValidID(){return m_iNextValidID;}
  
  //this can be used to reset the next ID
  static void  ResetNextValidID(){m_iNextValidID = 0;}
  


  Vector2D     Pos()const{return m_vPosition;}
  void         SetPos(Vector2D new_pos){m_vPosition = new_pos;}

  double       BRadius()const{return m_dBoundingRadius;}
  void         SetBRadius(double r){m_dBoundingRadius = r;}
  int          ID()const{return m_ID;}

  bool         IsTagged()const{return m_bTag;}
  void         Tag(){m_bTag = true;}
  void         UnTag(){m_bTag = false;}

  Vector2D     Scale()const{return m_vScale;}
  void         SetScale(Vector2D val){m_dBoundingRadius *= MaxOf(val.x, val.y)/MaxOf(m_vScale.x, m_vScale.y); m_vScale = val;}
  void         SetScale(double val){m_dBoundingRadius *= (val/MaxOf(m_vScale.x, m_vScale.y)); m_vScale = Vector2D(val, val);} 

  int          EntityType()const{return m_iType;}
  void         SetEntityType(int new_type){m_iType = new_type;}

};



      
#endif




