#include "battle.h"
#include "dialog_renderer.h"

void dqBattle_Init()
{
   dqBattle = (dqBattle_t*)dqMalloc( sizeof( dqBattle_t ) );

   dqBattle->state = dqBattleStateIntro;
}

void dqBattle_Cleanup()
{
   dqFree( dqBattle );
}

void dqBattle_Generate()
{
   // TODO: set up enemy groups based on the current map tile tiers
   dqBattle->state = dqBattleStateIntro;
   dqDialogRenderer_ResetScroll();
}
