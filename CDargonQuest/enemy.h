#pragma once

#include "common.h"

typedef struct dqBattleStats_t dqBattleStats_t;

typedef struct dqEnemy_t
{
   char name[ENTITY_NAME_SIZE];
   dqBattleStats_t* battleStats;
}
dqEnemy_t;

dqEnemy_t* dqEnemy_Generate();
void dqEnemy_Cleanup( dqEnemy_t* enemy );
