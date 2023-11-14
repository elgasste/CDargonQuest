#pragma once

#include "common.h"

// clipping an entity sometimes requires a tiny adjustment, so the entity's
// hit box doesn't accidentally end up in the wrong tile
#define COLLISION_ADJUSTMENT 0.001f;

typedef struct dqEntityOverworldState_t dqEntityOverworldState_t;

void dqPhysics_MoveEntity( dqEntityOverworldState_t* entityOverworldState );
void dqPhysics_DecelerateEntity( dqEntityOverworldState_t* entityOverworldState );
