#include "game_config.h"

void dqGameConfig_Init()
{
   dqGameConfig = (dqGameConfig_t*)malloc( sizeof( dqGameConfig_t ) );
   CHECK_MALLOC( dqGameConfig )

   dqGameConfig->mapTileSize = 16;

   dqGameConfig->playerVelocityStraight = 56;
   dqGameConfig->playerVelocityDiagonal = 44;
}

void dqGameConfig_Cleanup()
{
   SAFE_DELETE( dqGameConfig );
}
