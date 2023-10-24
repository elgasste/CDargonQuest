#include "title_input_handler.h"
#include "input_state.h"
#include "event_queue.h"
#include "menu.h"
#include "menu_option.h"

void dqTitleInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyDown ) )
   {
      dqMenu_ScrollDown( dqTitleMenu );
   }
   else if ( dqInputState_WasKeyPressed( sfKeyUp ) )
   {
      dqMenu_ScrollUp( dqTitleMenu );
   }
   else if ( dqInputState_WasKeyPressed( sfKeyReturn ) )
   {
      dqEventQueue_Push( dqTitleMenu->options[dqTitleMenu->selectedOption].eventType, 0 );
   }
}
