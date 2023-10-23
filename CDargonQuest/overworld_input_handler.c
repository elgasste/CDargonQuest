#include "overworld_input_handler.h"
#include "input_state.h"
#include "event_queue.h"

void dqOverworldInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyEscape ) )
   {
      dqEventQueue_Push( dqEventQuit );
   }
}
