#include "game_data.h"
#include "map_loader.h"

void dqGameData_Init()
{
   dqGameData = (dqGameData_t*)malloc( sizeof( dqGameData_t ) );

   dqMapLoader_LoadMaps();
}

void dqGameData_Cleanup()
{
   dqMapLoader_CleanupMaps();

   SAFE_DELETE( dqGameData );
}
