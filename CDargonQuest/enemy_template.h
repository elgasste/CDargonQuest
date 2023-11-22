#if !defined( DQ_ENEMY_TEMPLATE_H )
#define DQ_ENEMY_TEMPLATE_H

#include "common.h"
#include "indefinite_article.h"

typedef struct dqEnemyTemplate_t
{
   char name[ENTITY_NAME_LENGTH];
   dqIndefiniteArticle_t indefiniteArticle;

   unsigned int spriteSize;
   unsigned int spriteIndex;

   unsigned int minHitPoints;
   unsigned int maxHitPoints;

   unsigned int attackPower;
   unsigned int defensePower;
}
dqEnemyTemplate_t;

#endif
