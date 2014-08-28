#ifndef AUTOLIST_H
#define AUTOLIST_H

//------------------------------------------------------------------------
//
//Name:   Autolist.h
//
//Desc:   Inherit from this class to automatically create lists of
//        similar objects. Whenever an object is created it will
//        automatically be added to the list. Whenever it is destroyed
//        it will automatically be removed.
//
//Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <list>


template <class T>
class AutoList
{
public:

  typedef std::list<T*> ObjectList;
  
private:

  static ObjectList m_Members;

protected:

  AutoList()
  {
    //cast this object to type T* and add it to the list
    m_Members.push_back(static_cast<T*>(this));
  }

  ~AutoList()
  {
    m_Members.remove(static_cast<T*>(this));    
  }

public:


  static ObjectList& GetAllMembers(){return m_Members;}
};


template <class T>
std::list<T*> AutoList<T>::m_Members;



#endif