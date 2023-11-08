#pragma once

#include "common.h"

typedef struct dqGameConfig_t
{
   const char* logFileName;

   float mapTileSize;

   float playerVelocityStraight;
   float playerVelocityDiagonal;

   sfBool noClipCheat;
   sfBool invisibleCheat;
   sfBool tileStatCheat;
}
dqGameConfig_t;

dqGameConfig_t* dqGameConfig;

void dqGameConfig_Init();
void dqGameConfig_Cleanup();
