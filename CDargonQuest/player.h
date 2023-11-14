#pragma once

#include "common.h"

typedef struct dqEntityOverworldState_t dqEntityOverworldState_t;
typedef struct dqBattleStats_t dqBattleStats_t;

typedef struct dqPlayer_t
{
   dqEntityOverworldState_t* overworldState;
   dqBattleStats_t* battleStats;
}
dqPlayer_t;

dqPlayer_t* dqPlayer_Create();
void dqPlayer_Cleanup( dqPlayer_t* player );
