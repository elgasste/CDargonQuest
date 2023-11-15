#if !defined( DQ_GAME_CONFIG_H )
#define DQ_GAME_CONFIG_H

#include "common.h"

typedef struct dqGameConfig_t
{
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

#endif
