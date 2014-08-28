#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   MessageDispatcher.h
//
//  Desc:   A message dispatcher. Manages messages of the type Telegram.
//          Instantiated as a singleton.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <set>
#include <string>


#include "Messaging/Telegram.h"


class BaseGameEntity;


//to make life easier...
#define Dispatcher MessageDispatcher::Instance()

//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;


class MessageDispatcher
{
private:  
  
  //a std::set is used as the container for the delayed messages
  //because of the benefit of automatic sorting and avoidance
  //of duplicates. Messages are sorted by their dispatch time.
  std::set<Telegram> PriorityQ;

  //this method is utilized by DispatchMsg or DispatchDelayedMessages.
  //This method calls the message handling member function of the receiving
  //entity, pReceiver, with the newly created telegram
  void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

  MessageDispatcher(){}

  //copy ctor and assignment should be private
  MessageDispatcher(const MessageDispatcher&);
  MessageDispatcher& operator=(const MessageDispatcher&);

public:

  static MessageDispatcher* Instance();

  //send a message to another agent. Receiving agent is referenced by ID.
  void DispatchMsg(double      delay,
                   int         sender,
                   int         receiver,
                   int         msg,
                   void*       ExtraInfo);

  //send out any delayed messages. This method is called each time through   
  //the main game loop.
  void DispatchDelayedMessages();
};



#endif