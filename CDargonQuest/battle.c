#include "battle.h"
#include "dialog_renderer.h"

void dqBattle_Init()
{
   dqBattle = (dqBattle_t*)dqMalloc( sizeof( dqBattle_t ) );
}

void dqBattle_Cleanup()
{
   dqFree( dqBattle );
}

void dqBattle_Generate()
{
   // TODO: set up enemy groups based on the current map tile tiers
   dqBattle_SetState( dqBattleStateIntro );
}

void dqBattle_SetState( dqBattleState state )
{
   dqBattle->state = state;
   dqDialogRenderer_ResetScroll();
}
