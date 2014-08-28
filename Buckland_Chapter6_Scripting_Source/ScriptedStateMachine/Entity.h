#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------------------------------------------
//
//  Name:   Entity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>


class Entity
{

private:

  int          m_ID;

  std::string  m_Name;

  //used by the constructor to give each entity a unique ID
  int NextValidID(){static int NextID = 0; return NextID++;}

public:

  Entity(std::string name = "NoName"):m_ID(NextValidID()), m_Name(name)
  {}

  virtual ~Entity()
  {}

  //all entities must implement an update function
  virtual void  Update()=0;

  //accessors
  int         ID()const{return m_ID;}  
  std::string Name()const{return m_Name;}

};




#endif


