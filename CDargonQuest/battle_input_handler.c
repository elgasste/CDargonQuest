#include "battle_input_handler.h"
#include "input_state.h"
#include "event_queue.h"
#include "battle.h"

static void dqBattleInputHandler_HandleIntroState()
{
   if ( dqInputState->keyWasPressed )
   {
      dqBattle_SetState( dqBattleStateResult );
   }
}

static void dqBattleInputHandler_HandleResultState()
{
   if ( dqInputState->keyWasPressed )
   {
      dqEventQueue_Push( dqEventExitBattle, 0 );
   }
}

void dqBattleInputHandler_HandleInput()
{
   switch ( dqBattle->state )
   {
      case dqBattleStateIntro:
         dqBattleInputHandler_HandleIntroState();
         break;
      case dqBattleStateResult:
         dqBattleInputHandler_HandleResultState();
         break;
   }
}
