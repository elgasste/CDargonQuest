#pragma once

#include "common.h"

typedef struct dqEntity_t dqEntity_t;

void dqCollision_MoveEntity( dqEntity_t* entity );
void dqCollision_ClipEntity( dqEntity_t* entity );