#include "game_config.h"
#include "game_data.h"
#include "map_loader.h"
#include "player.h"
#include "map.h"

void dqGameData_Init()
{
   dqGameData = (dqGameData_t*)dqMalloc( sizeof( dqGameData_t ) );

   dqMapLoader_LoadMaps();

   dqGameData->playerStartTileCoordinates.x = 28;
   dqGameData->playerStartTileCoordinates.y = 35;
   dqGameData->player = dqPlayer_Create();
}

void dqGameData_Cleanup()
{
   dqMapLoader_CleanupMaps();
   dqPlayer_Cleanup( dqGameData->player );

   dqFree( dqGameData );
}

dqMap_t* dqGameData_GetCurrentMap()
{
   return &( dqGameData->maps[dqGameData->currentMapIndex] );
}
