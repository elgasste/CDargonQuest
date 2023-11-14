#include "enemy.h"
#include "battle_stats.h"

dqEnemy_t* dqEnemy_Generate()
{
   dqEnemy_t* enemy = (dqEnemy_t*)dqMalloc( sizeof( dqEnemy_t ) );
   enemy->battleStats = (dqBattleStats_t*)dqMalloc( sizeof( dqBattleStats_t ) );

   // TODO: this will come from game data, which will have a tiered array of
   // enemy templates. from there we can randomzie actual hit point values.
   sprintf_s( enemy->name, ENTITY_NAME_SIZE, "woooooo" );
   enemy->battleStats->hitPoints = 15;
   enemy->battleStats->attackPower = 3;
   enemy->battleStats->defensePower = 1;

   return enemy;
}

void dqEnemy_Cleanup( dqEnemy_t* enemy )
{
   dqFree( enemy );
}
