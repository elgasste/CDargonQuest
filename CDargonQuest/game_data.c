#include "game_config.h"
#include "game_data.h"
#include "map_loader.h"
#include "entity.h"
#include "map.h"

void dqGameData_Init()
{
   dqEntity_t* player;
   dqMap_t* map;
   dqMapTile_t* tile;

   dqGameData = (dqGameData_t*)dqMalloc( sizeof( dqGameData_t ) );

   dqGameData->playerStartTileCoordinates.x = 28;
   dqGameData->playerStartTileCoordinates.y = 35;

   dqMapLoader_LoadMaps();

   dqGameData->player = (dqEntity_t*)dqMalloc( sizeof( dqEntity_t ) );

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

   map = dqGameData_GetCurrentMap();
   tile = dqMap_GetTileFromPosition( map, &( player->centerPosition ) );
   map->playerTileCache = tile;
}

void dqGameData_Cleanup()
{
   dqMapLoader_CleanupMaps();

   dqFree( dqGameData->player );
   dqFree( dqGameData );
}

dqMap_t* dqGameData_GetCurrentMap()
{
   return &( dqGameData->maps[dqGameData->currentMapIndex] );
}
