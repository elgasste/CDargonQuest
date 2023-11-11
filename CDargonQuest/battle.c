#include "battle.h"
#include "menu.h"
#include "dialog_renderer.h"

void dqBattle_Init()
{
   dqBattle = (dqBattle_t*)dqMalloc( sizeof( dqBattle_t ) );

   dqBattle->resultMessage[0] = '\0';
}

void dqBattle_Cleanup()
{
   dqFree( dqBattle );
}

void dqBattle_Generate()
{
   // TODO: set up enemy groups based on the current map tile tiers
   dqMenuBattleAction->selectedOption = 0;
   dqBattle_SetState( dqBattleStateIntro );
}

void dqBattle_SetState( dqBattleState state )
{
   dqBattle->state = state;
   dqDialogRenderer_ResetScroll();
}

void dqBattle_Attack()
{
   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "Your killing spree was a success!" );
      dqBattle_SetState( dqBattleStateResult );
   }
}

void dqBattle_Run()
{
   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "Wow, so brave. At least you got away, I guess." );
      dqBattle_SetState( dqBattleStateResult );
   }
}
