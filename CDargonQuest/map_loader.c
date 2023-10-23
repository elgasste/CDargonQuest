#include "map_loader.h"
#include "game_data.h"

void dqMapLoader_LoadMaps()
{
   // TODO: just one map for now, but more to come later
   dqGameData->mapCount = 1;
   dqGameData->maps = (dqMap_t*)malloc( sizeof( dqMap_t ) );

   // TODO: actually load tiles
#pragma warning ( suppress:6011 )
   dqGameData->maps[0].tiles = NULL;
}

void dqMapLoader_CleanupMaps()
{
   unsigned int i;

   for ( i = 0; i < dqGameData->mapCount; i++ )
   {
      SAFE_DELETE( dqGameData->maps[i].tiles );
   }

   SAFE_DELETE( dqGameData->maps );
}
