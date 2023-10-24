#include "game_data.h"
#include "map_loader.h"
#include "render_config.h"

void dqGameData_Init()
{
   dqGameData = (dqGameData_t*)malloc( sizeof( dqGameData_t ) );

   dqMapLoader_LoadMaps();

#pragma warning ( suppress:6011 )
   dqGameData->player = (dqEntity_t*)malloc( sizeof( dqEntity_t ) );

#pragma warning ( suppress:6011 )
   dqGameData->player->centerPosition.x = dqRenderConfig->screenWidth / 2;
   dqGameData->player->centerPosition.y = dqRenderConfig->screenHeight / 2;
   dqGameData->player->hitBoxSize.x = 12;
   dqGameData->player->hitBoxSize.y = 12;
   dqGameData->player->hitBoxPosition.x = dqGameData->player->centerPosition.x - ( dqGameData->player->hitBoxSize.x / 2 );
   dqGameData->player->hitBoxPosition.y = dqGameData->player->centerPosition.y - ( dqGameData->player->hitBoxSize.y / 2 );
   dqGameData->player->velocityX = 0;
   dqGameData->player->velocityY = 0;
   dqGameData->player->direction = dqDirectionDown;
}

void dqGameData_Cleanup()
{
   dqMapLoader_CleanupMaps();

   SAFE_DELETE( dqGameData->player );
   SAFE_DELETE( dqGameData );
}
