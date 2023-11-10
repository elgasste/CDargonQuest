#include "battle_input_handler.h"
#include "input_state.h"
#include "event_queue.h"

void dqBattleInputHandler_HandleInput()
{
   if ( dqInputState->keyWasPressed )
   {
      dqEventQueue_Push( dqEventExitBattle, 0 );
   }
}
