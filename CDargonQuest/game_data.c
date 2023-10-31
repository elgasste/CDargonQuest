#include "game_config.h"
#include "game_data.h"
#include "map_loader.h"
#include "entity.h"
#include "map.h"

void dqGameData_Init()
{
   dqEntity_t* player;

   dqGameData = (dqGameData_t*)malloc( sizeof( dqGameData_t ) );
   CHECK_MALLOC( dqGameData )

   dqGameData->playerStartTileCoordinates.x = 28;
   dqGameData->playerStartTileCoordinates.y = 35;

   dqMapLoader_LoadMaps();

   dqGameData->player = (dqEntity_t*)malloc( sizeof( dqEntity_t ) );
   CHECK_MALLOC( dqGameData->player )

   // TODO: most of this will eventually be loaded from a file
   player = dqGameData->player;
   player->hitBoxSize.x = 14;
   player->hitBoxSize.y = 14;
   player->hitBoxPosition.x = dqGameData->playerStartTileCoordinates.x * dqGameConfig->mapTileSize;
   player->hitBoxPosition.y = dqGameData->playerStartTileCoordinates.y * dqGameConfig->mapTileSize;
   player->centerPosition.x = player->hitBoxPosition.x + ( player->hitBoxSize.x / 2 );
   player->centerPosition.y = player->hitBoxPosition.y + ( player->hitBoxSize.y / 2 );
   player->velocityX = 0;
   player->velocityY = 0;
   player->direction = dqDirectionDown;
}

void dqGameData_Cleanup()
{
   dqMapLoader_CleanupMaps();

   SAFE_DELETE( dqGameData->player );
   SAFE_DELETE( dqGameData );
}

dqMap_t* dqGameData_GetCurrentMap()
{
   return &( dqGameData->maps[dqGameData->currentMapIndex] );
}
