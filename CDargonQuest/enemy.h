#if !defined( DQ_ENEMY_H )
#define DQ_ENEMY_H

#include "common.h"
#include "indefinite_article.h"

typedef struct dqBattleStats_t dqBattleStats_t;

typedef struct dqEnemy_t
{
   char name[ENTITY_NAME_SIZE];
   dqIndefiniteArticle_t indefiniteArticle;

   unsigned int spriteSize;
   sfSprite* sprite;

   dqBattleStats_t* battleStats;
}
dqEnemy_t;

dqEnemy_t* dqEnemy_Generate( unsigned int tier, unsigned int index );
void dqEnemy_Cleanup( dqEnemy_t* enemy );

#endif
