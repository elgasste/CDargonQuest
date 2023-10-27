#include "map_loader.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"
#include "collision_map.h"
#include "collision_tile.h"
#include "render_config.h"
#include "game_config.h"

void dqMapLoader_LoadMaps()
{
   unsigned int i, id1 = 0, id2 = 1, idTemp;
   dqMap_t* map;

   // TODO: just one temporary map for now, but more to come later
   dqGameData->mapCount = 1;
   dqGameData->maps = (dqMap_t*)malloc( sizeof( dqMap_t ) );
   CHECK_MALLOC( dqGameData->maps )

   map = &( dqGameData->maps[0] );

   map->columns = 60;
   map->rows = 40;
   map->size.x = map->columns * dqRenderConfig->tileSize;
   map->size.y = map->rows * dqRenderConfig->tileSize;
   map->tileCount = map->columns * map->rows;
   map->tiles = (dqMapTile_t*)malloc( sizeof( dqMapTile_t ) * map->tileCount );
   CHECK_MALLOC( map->tiles )

   for ( i = 0; i < map->tileCount; i++ )
   {
      // this makes a checkerboard
      if ( i % map->columns == 0 )
      {
         idTemp = id1;
         id1 = id2;
         id2 = idTemp;
      }

      map->tiles[i].textureId = 0;
      map->tiles[i].tileId = ( i % 2 == 0 ) ? id1 : id2;
   }

   map->collisionMap = (dqCollisionMap_t*)malloc( sizeof( dqCollisionMap_t ) );
   CHECK_MALLOC( map->collisionMap )

   map->collisionMap->columns = 120;
   map->collisionMap->rows = 80;
   map->collisionMap->size.x = map->collisionMap->columns * dqGameConfig->collisionTileSize;
   map->collisionMap->size.y = map->collisionMap->rows * dqGameConfig->collisionTileSize;
   map->collisionMap->tileCount = map->collisionMap->columns * map->collisionMap->rows;
   map->collisionMap->tiles = (dqCollisionTile_t*)malloc( sizeof( dqCollisionTile_t ) * map->collisionMap->tileCount );
   CHECK_MALLOC( map->collisionMap->tiles )

   for ( i = 0; i < map->collisionMap->tileCount; i++ )
   {
      map->collisionMap->tiles[i].isPassable = sfTrue;
      map->collisionMap->tiles[i].slowsMovement = sfFalse;
      map->collisionMap->tiles[i].isWater = sfFalse;
      map->collisionMap->tiles[i].damage = 0;
   }
}

void dqMapLoader_CleanupMaps()
{
   unsigned int i;

   for ( i = 0; i < dqGameData->mapCount; i++ )
   {
      SAFE_DELETE( dqGameData->maps[i].collisionMap->tiles );
      SAFE_DELETE( dqGameData->maps[i].collisionMap );
      SAFE_DELETE( dqGameData->maps[i].tiles );
   }

   SAFE_DELETE( dqGameData->maps );
}
