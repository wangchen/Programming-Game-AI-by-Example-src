#ifndef RAVEN_MESSAGES_H
#define RAVEN_MESSAGES_H
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Messages.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   file to enumerate the messages a Raven_Bot must be able to handle
//-----------------------------------------------------------------------------
#include <string>

enum message_type
{
  Msg_Blank,
  Msg_PathReady,
  Msg_NoPathAvailable,
  Msg_TakeThatMF, 
  Msg_YouGotMeYouSOB,
  Msg_GoalQueueEmpty,
  Msg_OpenSesame,
  Msg_GunshotSound,
  Msg_UserHasRemovedBot
};

//used for outputting debug info
inline std::string MessageToString(int msg)
{
  switch(msg)
  {
  case Msg_PathReady:

    return "Msg_PathReady";

  case Msg_NoPathAvailable:

    return "Msg_NoPathAvailable";

  case Msg_TakeThatMF:

    return "Msg_TakeThatMF";

  case Msg_YouGotMeYouSOB:

    return "Msg_YouGotMeYouSOB";

  case Msg_GoalQueueEmpty:

    return "Msg_GoalQueueEmpty";

  case Msg_OpenSesame:

    return "Msg_OpenSesame";

  case Msg_GunshotSound:

    return "Msg_GunshotSound";

  case Msg_UserHasRemovedBot:

    return "Msg_UserHasRemovedBot";

  default:

    return "Undefined message!";
  }
}


#endif