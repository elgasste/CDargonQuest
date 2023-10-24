#include "map_loader.h"
#include "game_data.h"

void dqMapLoader_LoadMaps()
{
   unsigned int tileCount, i;

   // TODO: just one temporary map for now, but more to come later
   dqGameData->mapCount = 1;
   dqGameData->maps = (dqMap_t*)malloc( sizeof( dqMap_t ) );

#pragma warning ( suppress:6011 )
   dqGameData->maps[0].width = 30;
   dqGameData->maps[0].height = 20;
   tileCount = dqGameData->maps[0].width * dqGameData->maps[0].height;
   dqGameData->maps[0].tiles = (dqMapTile_t*)malloc( sizeof( dqMapTile_t ) * tileCount );

   for ( i = 0; i < tileCount; i++ )
   {
#pragma warning ( suppress:6011 )
      dqGameData->maps[0].tiles[i].textureId = 0;
      dqGameData->maps[0].tiles[i].tileId = ( i % 2 == 0 ) ? 0 : 1;
      dqGameData->maps[0].tiles[i].isPassable = sfTrue;
   }
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
