#include "game_config.h"

void dqGameConfig_Init()
{
   dqGameConfig = (dqGameConfig_t*)malloc( sizeof( dqGameConfig_t ) );
   CHECK_MALLOC( dqGameConfig )

   dqGameConfig->logFileName = "log.txt";

   dqGameConfig->mapTileSize = 16;

   dqGameConfig->playerVelocityStraight = 56;
   dqGameConfig->playerVelocityDiagonal = 44;

   dqGameConfig->noClipCheat = sfFalse;
   dqGameConfig->invisibleCheat = sfFalse;
   dqGameConfig->tileStatCheat = sfFalse;
}

void dqGameConfig_Cleanup()
{
   SAFE_DELETE( dqGameConfig )
}
