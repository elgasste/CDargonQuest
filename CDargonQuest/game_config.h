#if !defined( DQ_GAME_CONFIG_H )
#define DQ_GAME_CONFIG_H

#include "common.h"

typedef struct dqGameConfig_t
{
   float mapTileSize;

   float playerVelocityStraight;
   float playerVelocityDiagonal;
   float playerVelocityStraightFast;
   float playerVelocityDiagonalFast;

   sfBool noClipCheat;
   sfBool invisibleCheat;
   sfBool tileStatCheat;
   sfBool fastCheat;
}
dqGameConfig_t;

dqGameConfig_t* dqGameConfig;

void dqGameConfig_Init();
void dqGameConfig_Cleanup();

#endif
