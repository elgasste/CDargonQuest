#pragma once

#include "common.h"

// clipping an entity sometimes requires a tiny adjustment, so the entity's
// hit box doesn't accidentally end up in the wrong tile
#define COLLISION_ADJUSTMENT 0.001f;

typedef struct dqEntity_t dqEntity_t;

void dqPhysics_MoveEntity( dqEntity_t* entity );
void dqPhysics_DecelerateEntity( dqEntity_t* entity );
