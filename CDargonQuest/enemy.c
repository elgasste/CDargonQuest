#include "enemy.h"
#include "game_data.h"
#include "render_config.h"
#include "render_data.h"
#include "enemy_template.h"
#include "battle_stats.h"
#include "random.h"

dqEnemy_t* dqEnemy_Generate( unsigned int tier, unsigned int index )
{
   sfIntRect textureRect;
   dqEnemyTemplate_t* template = &( dqGameData->enemyTemplates[tier][index] );
   dqEnemy_t* enemy = (dqEnemy_t*)dqMalloc( sizeof( dqEnemy_t ), sfTrue );
   enemy->battleStats = (dqBattleStats_t*)dqMalloc( sizeof( dqBattleStats_t ), sfTrue );

   sprintf_s( enemy->name, ENTITY_NAME_SIZE, template->name );
   enemy->indefiniteArticle = template->indefiniteArticle;
   enemy->spriteSize = template->spriteSize;
   enemy->battleStats->hitPoints = dqRandom_UnsignedInt( template->minHitPoints, template->maxHitPoints );
   enemy->battleStats->attackPower = template->attackPower;
   enemy->battleStats->defensePower = template->defensePower;

   enemy->sprite = sfSprite_create();
   sfSprite_setTexture( enemy->sprite, dqRenderData->enemyTextures[enemy->spriteSize], sfFalse );
   textureRect.left = template->spriteIndex * dqRenderConfig->enemySpriteWidths[enemy->spriteSize];
   textureRect.top = dqRenderConfig->enemySpriteHeight * tier;
   textureRect.width = dqRenderConfig->enemySpriteWidths[enemy->spriteSize];
   textureRect.height = dqRenderConfig->enemySpriteHeight;
   sfSprite_setTextureRect( enemy->sprite, textureRect );

   return enemy;
}

void dqEnemy_Cleanup( dqEnemy_t* enemy )
{
   sfSprite_destroy( enemy->sprite );

   dqFree( enemy->battleStats, sizeof( dqBattleStats_t ), sfTrue );
   dqFree( enemy, sizeof( dqEnemy_t ), sfTrue );
}
