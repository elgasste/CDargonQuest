#include "map_loader.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"
#include "render_config.h"

void dqMapLoader_LoadMaps()
{
   unsigned int i, id1 = 0, id2 = 1, idTemp;

   // TODO: just one temporary map for now, but more to come later
   dqGameData->mapCount = 1;
   dqGameData->maps = (dqMap_t*)malloc( sizeof( dqMap_t ) );
   CHECK_MALLOC( dqGameData->maps )

   dqGameData->maps[0].columns = 100;
   dqGameData->maps[0].rows = 60;
   dqGameData->maps[0].width = dqGameData->maps[0].columns * dqRenderConfig->tileSize;
   dqGameData->maps[0].height = dqGameData->maps[0].rows * dqRenderConfig->tileSize;
   dqGameData->maps[0].tileCount = dqGameData->maps[0].columns * dqGameData->maps[0].rows;
   dqGameData->maps[0].tiles = (dqMapTile_t*)malloc( sizeof( dqMapTile_t ) * dqGameData->maps[0].tileCount );
   CHECK_MALLOC( dqGameData->maps[0].tiles )

   for ( i = 0; i < dqGameData->maps[0].tileCount; i++ )
   {
      // this makes a checkerboard
      if ( i % dqGameData->maps[0].columns == 0 )
      {
         idTemp = id1;
         id1 = id2;
         id2 = idTemp;
      }

      dqGameData->maps[0].tiles[i].textureId = 0;
      dqGameData->maps[0].tiles[i].tileId = ( i % 2 == 0 ) ? id1 : id2;
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
