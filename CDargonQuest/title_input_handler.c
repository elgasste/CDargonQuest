#include "common.h"
#include "title_input_handler.h"
#include "input_state.h"
#include "event_queue.h"

void dqTitleInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyEscape ) )
   {
      dqEventQueue_Push( dqEventQuit );
   }
}
