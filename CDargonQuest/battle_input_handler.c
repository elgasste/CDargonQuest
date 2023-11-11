#include "battle_input_handler.h"
#include "input_state.h"
#include "event_queue.h"
#include "battle.h"
#include "menu.h"
#include "menu_option.h"

static void dqBattleInputHandler_HandleIntroState()
{
   if ( dqInputState->keyWasPressed )
   {
      dqBattle_SetState( dqBattleStateSelectAction );
   }
}

static void dqBattleInputHandler_HandleResultState()
{
   if ( dqInputState->keyWasPressed )
   {
      dqEventQueue_Push( dqEventBattleExit, 0 );
   }
}

void dqBattleInputHandler_HandleInput()
{
   switch ( dqBattle->state )
   {
      case dqBattleStateIntro:
         dqBattleInputHandler_HandleIntroState();
         break;
      case dqBattleStateSelectAction:
         dqMenu_HandleInputDefault( dqMenuBattleAction );
         break;
      case dqBattleStateResult:
         dqBattleInputHandler_HandleResultState();
         break;
   }
}
