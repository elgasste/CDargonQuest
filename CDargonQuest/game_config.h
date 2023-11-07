#pragma once

#include "common.h"

typedef struct dqGameConfig_t
{
   float mapTileSize;

   float playerVelocityStraight;
   float playerVelocityDiagonal;

   sfBool noClipCheat;
   sfBool passableCheat;
}
dqGameConfig_t;

dqGameConfig_t* dqGameConfig;

void dqGameConfig_Init();
void dqGameConfig_Cleanup();
