#include "battle_renderer.h"

void dqBattleRenderer_Init()
{
   dqBattleRenderer = (dqBattleRenderer_t*)malloc( sizeof( dqBattleRenderer_t ) );
   CHECK_MALLOC( dqBattleRenderer )
}

void dqBattleRenderer_Cleanup()
{
   SAFE_DELETE( dqBattleRenderer )
}

void dqBattleRenderer_Render()
{
   // TODO
}
