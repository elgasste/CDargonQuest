#include "game_config.h"

void dqGameConfig_Init()
{
   dqGameConfig = (dqGameConfig_t*)dqMalloc( sizeof( dqGameConfig_t ), sfTrue );

   dqGameConfig->mapTileSize = 16;

   dqGameConfig->playerVelocityStraight = 56;
   dqGameConfig->playerVelocityDiagonal = 44;
   dqGameConfig->playerVelocityStraightFast = 256;
   dqGameConfig->playerVelocityDiagonalFast = 200;

   dqGameConfig->noClipCheat = sfFalse;
   dqGameConfig->invisibleCheat = sfFalse;
   dqGameConfig->tileStatCheat = sfFalse;
   dqGameConfig->fastCheat = sfFalse;
}

void dqGameConfig_Cleanup()
{
   dqFree( dqGameConfig, sizeof( dqGameConfig_t ), sfTrue );
}
