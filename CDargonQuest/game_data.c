#include "game_data.h"
#include "map_loader.h"
#include "entity.h"
#include "map.h"

void dqGameData_Init()
{
   dqGameData = (dqGameData_t*)malloc( sizeof( dqGameData_t ) );
   CHECK_MALLOC( dqGameData )

   dqMapLoader_LoadMaps();

   dqGameData->player = (dqEntity_t*)malloc( sizeof( dqEntity_t ) );
   CHECK_MALLOC( dqGameData->player )

   // TODO: each map will have entrance and exit points depending on where the player just came from
   dqGameData->player->centerPosition.x = dqGameData->maps[0].size.x / 2;
   dqGameData->player->centerPosition.y = dqGameData->maps[0].size.y / 2;
   dqGameData->player->hitBoxSize.x = 14;
   dqGameData->player->hitBoxSize.y = 14;
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
