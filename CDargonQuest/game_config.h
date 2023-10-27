#pragma once

#include "common.h"

typedef struct dqGameConfig_t
{
   float collisionTileSize;

   float playerVelocityStraight;
   float playerVelocityDiagonal;
}
dqGameConfig_t;

dqGameConfig_t* dqGameConfig;

void dqGameConfig_Init();
void dqGameConfig_Cleanup();
