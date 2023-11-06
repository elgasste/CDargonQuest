#include "map.h"
#include "map_tile.h"
#include "game_config.h"
#include "game_data.h"
#include "entity.h"

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
   // TODO: figure out a way to animate a fade-out/fade-in between maps
   dqEntity_t* player = dqGameData->player;
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile = dqMap_GetTileFromPosition( map, &( player->centerPosition ) );
   unsigned int entranceColumn, entranceRow;

   if ( tile->isExit )
   {
      dqGameData->currentMapIndex = tile->exitMapIndex;
      map = dqGameData_GetCurrentMap();

      entranceColumn = tile->entranceTileIndex % map->columns;
      entranceRow = tile->entranceTileIndex / map->columns;

      player->hitBoxPosition.x = entranceColumn * dqGameConfig->mapTileSize;
      player->hitBoxPosition.y = entranceRow * dqGameConfig->mapTileSize;

      player->centerPosition.x = player->hitBoxPosition.x + ( player->hitBoxSize.x / 2 );
      player->centerPosition.y = player->hitBoxPosition.y + ( player->hitBoxSize.y / 2 );
   }
}
