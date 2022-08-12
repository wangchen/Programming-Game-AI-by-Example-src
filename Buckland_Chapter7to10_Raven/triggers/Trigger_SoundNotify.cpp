#include "Trigger_SoundNotify.h"
#include "Triggers/TriggerRegion.h"
#include "../Raven_Game.h"
#include "../lua/Raven_Scriptor.h"
#include "../constants.h"
#include "Messaging/MessageDispatcher.h"
#include "../Raven_Messages.h"

#include "misc/cgdi.h"

//------------------------------ ctor -----------------------------------------
//-----------------------------------------------------------------------------

Trigger_SoundNotify::Trigger_SoundNotify(Raven_Bot* source,
                                     double      range):Trigger_LimitedLifetime<Raven_Bot>(FrameRate /script->GetInt("Bot_TriggerUpdateFreq")),
                                                       m_pSoundSource(source)
{
  //set position and range
  SetPos(m_pSoundSource->Pos());

  SetBRadius(range);

  //create and set this trigger's region of fluence
  AddCircularTriggerRegion(Pos(), BRadius());
}


//------------------------------ Try ------------------------------------------
//
//  when triggered this trigger adds the bot that made the source of the sound 
//  to the triggering bot's perception.
//-----------------------------------------------------------------------------
void Trigger_SoundNotify::Try(Raven_Bot* pBot)
{
  //is this bot within range of this sound
  if (isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
  {
    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            SENDER_ID_IRRELEVANT,
                            pBot->ID(),
                            Msg_GunshotSound,
                            m_pSoundSource);
  }   
}

