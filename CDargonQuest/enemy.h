#pragma once

#include "common.h"
#include "indefinite_article.h"

typedef struct dqBattleStats_t dqBattleStats_t;

typedef struct dqEnemy_t
{
   char name[ENTITY_NAME_SIZE];
   dqIndefiniteArticle_t indefiniteArticle;

   dqBattleStats_t* battleStats;
}
dqEnemy_t;

void dqEnemy_Cleanup( dqEnemy_t* enemy );
