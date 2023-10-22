#include "input_handler.h"
#include "input_state.h"
#include "event_queue.h"

void dqInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyEscape ) )
   {
      dqEventQueue_Push( eventQuit );
   }
}
