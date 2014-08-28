#ifndef TRIGGER_SEND_MESSAGE_H
#define TRIGGER_SEND_MESSAGE_H
///-----------------------------------------------------------------------------
//
//  Name:   Trigger_OnButtonSendMsg.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   trigger class to define a button that sends a msg to a 
//          specific entity when activated.
//-----------------------------------------------------------------------------
#include "Triggers/Trigger.h"
#include "Messaging/MessageDispatcher.h"
#include "misc/cgdi.h"

template <class entity_type>
class Trigger_OnButtonSendMsg : public Trigger<entity_type>
{
private:

  //when triggered a message is sent to the entity with the following ID
  unsigned int    m_iReceiver;

  //the message that is sent
  int             m_iMessageToSend;

public:

  Trigger_OnButtonSendMsg(std::ifstream& datafile):
      
      Trigger<entity_type>(GetValueFromStream<int>(datafile))
  {
     Read(datafile);
   }

  void Try(entity_type* pEnt);

  void Update();
  
  void Render();

  void Write(std::ostream&  os)const{}
  void Read (std::ifstream& is);

  bool HandleMessage(const Telegram& msg);
};


///////////////////////////////////////////////////////////////////////////////



template <class entity_type>
void  Trigger_OnButtonSendMsg<entity_type>::Try(entity_type* pEnt)
{

  if (isTouchingTrigger(pEnt->Pos(), pEnt->BRadius()))
  {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              this->ID(),
                              m_iReceiver,
                              m_iMessageToSend,
                              NO_ADDITIONAL_INFO);

  }
}

template <class entity_type>
void Trigger_OnButtonSendMsg<entity_type>::Update()
{
}

template <class entity_type>
void Trigger_OnButtonSendMsg<entity_type>::Render()
{
 gdi->OrangePen();

  double sz = BRadius();  

  gdi->Line(Pos().x - sz, Pos().y - sz, Pos().x + sz, Pos().y - sz);
  gdi->Line(Pos().x + sz, Pos().y - sz, Pos().x + sz, Pos().y + sz);
  gdi->Line(Pos().x + sz, Pos().y + sz, Pos().x - sz, Pos().y + sz);
  gdi->Line(Pos().x - sz, Pos().y + sz, Pos().x - sz, Pos().y - sz);
}

template <class entity_type>
void Trigger_OnButtonSendMsg<entity_type>::Read(std::ifstream& is)
{
  //grab the id of the entity it messages
  is >> m_iReceiver;

  //grab the message type
  is >> m_iMessageToSend;

  //grab the position and radius
  double x,y,r;
  is >> x >> y >> r;

  SetPos(Vector2D(x,y));
  SetBRadius(r);

  //create and set this trigger's region of fluence
  AddRectangularTriggerRegion(Pos()-Vector2D(BRadius(), BRadius()),   //top left corner
                              Pos()+Vector2D(BRadius(), BRadius()));  //bottom right corner
}

template <class entity_type>
bool Trigger_OnButtonSendMsg<entity_type>::HandleMessage(const Telegram& msg)
{
  return false;
}

#endif
