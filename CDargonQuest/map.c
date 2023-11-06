#include "map.h"
#include "map_tile.h"
#include "game_config.h"
#include "game_data.h"
#include "entity.h"
#include "event_queue.h"

dqMapTile_t* dqMap_GetTileFromCoordinates( dqMap_t* map, unsigned int column, unsigned int row )
{
   unsigned int tileIndex = ( row * map->columns ) + column;
   return &( map->tiles[tileIndex] );
}

dqMapTile_t* dqMap_GetTileFromPosition( dqMap_t* map, sfVector2f* pos )
{
   unsigned int column = (unsigned int)( pos->x / dqGameConfig->mapTileSize );
   unsigned int row = (unsigned int)( pos->y / dqGameConfig->mapTileSize );

   return &( map->tiles[ ( row * map->columns ) + column ] );
}

void dqMap_CheckSwap()
{
   dqMapTile_t* tile = dqMap_GetTileFromPosition( dqGameData_GetCurrentMap(), &( dqGameData->player->centerPosition ));

   if ( tile->isExit )
   {
      dqEventQueue_Push( dqEventSwapMap, 2, (int)tile->exitMapIndex, (int)tile->entranceTileIndex );
   }
}
