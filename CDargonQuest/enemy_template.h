#pragma once

#include "common.h"
#include "indefinite_article.h"

typedef struct dqEnemyTemplate_t
{
   char name[ENTITY_NAME_SIZE];
   dqIndefiniteArticle_t indefiniteArticle;

   unsigned int minHitPoints;
   unsigned int maxHitPoints;

   unsigned int attackPower;
   unsigned int defensePower;
}
dqEnemyTemplate_t;
