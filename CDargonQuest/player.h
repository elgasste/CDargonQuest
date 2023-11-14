#pragma once

#include "common.h"

typedef struct dqEntityOverworldState_t dqEntityOverworldState_t;

typedef struct dqPlayer_t
{
   dqEntityOverworldState_t* overworldState;
}
dqPlayer_t;

dqPlayer_t* dqPlayer_Create();
void dqPlayer_Cleanup( dqPlayer_t* player );
