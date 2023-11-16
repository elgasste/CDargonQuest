#include "enemy.h"
#include "game_data.h"
#include "enemy_template.h"
#include "battle_stats.h"
#include "random.h"

dqEnemy_t* dqEnemy_Generate( unsigned int tier, unsigned int index )
{
   dqEnemyTemplate_t* template = &( dqGameData->enemyTemplates[tier][index] );
   dqEnemy_t* enemy = (dqEnemy_t*)dqMalloc( sizeof( dqEnemy_t ), sfTrue );
   enemy->battleStats = (dqBattleStats_t*)dqMalloc( sizeof( dqBattleStats_t ), sfTrue );

   sprintf_s( enemy->name, ENTITY_NAME_SIZE, template->name );
   enemy->indefiniteArticle = template->indefiniteArticle;
   enemy->battleStats->hitPoints = dqRandom_UnsignedInt( template->minHitPoints, template->maxHitPoints );
   enemy->battleStats->attackPower = template->attackPower;
   enemy->battleStats->defensePower = template->defensePower;

   return enemy;
}

void dqEnemy_Cleanup( dqEnemy_t* enemy )
{
   dqFree( enemy->battleStats, sizeof( dqBattleStats_t ), sfTrue );
   dqFree( enemy, sizeof( dqEnemy_t ), sfTrue );
}
