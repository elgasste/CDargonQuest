#include "common.h"
#include "title_input_handler.h"
#include "input_state.h"
#include "event_queue.h"
#include "game.h"

void dqTitleInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyDown ) )
   {
      dqMenu_ScrollDown( dqGame->titleMenu );
   }
   else if ( dqInputState_WasKeyPressed( sfKeyUp ) )
   {
      dqMenu_ScrollUp( dqGame->titleMenu );
   }
   else if ( dqInputState_WasKeyPressed( sfKeyReturn ) )
   {
      dqEventQueue_Push( dqGame->titleMenu->options[dqGame->titleMenu->selectedOption].eventType );
   }
}
