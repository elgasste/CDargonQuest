#include "game_config.h"

void dqGameConfig_Init()
{
   dqGameConfig = (dqGameConfig_t*)malloc( sizeof( dqGameConfig_t ) );

#pragma warning ( suppress:6011 )
   dqGameConfig->playerVelocityStraight = 56;
   dqGameConfig->playerVelocityDiagonal = 44;
}

void dqGameConfig_Cleanup()
{
   SAFE_DELETE( dqGameConfig );
}
