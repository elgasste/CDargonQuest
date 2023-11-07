#include "map.h"
#include "map_tile.h"
#include "game_config.h"
#include "game_data.h"
#include "entity.h"
#include "event_queue.h"
#include "random.h"

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
   dqMapTile_t* tile;

   if ( !dqGameConfig->noClipCheat )
   {
      tile = dqMap_GetTileFromPosition( dqGameData_GetCurrentMap(), &( dqGameData->player->centerPosition ));

      if ( tile->isExit )
      {
         dqEventQueue_Push( dqEventSwapMap, 2, (int)tile->exitMapIndex, (int)tile->entranceTileIndex );
      }  
   }
}

void dqMap_Swap( unsigned int newMapIndex, unsigned int newTileIndex )
{
   unsigned int newColumn, newRow;
   dqEntity_t* player = dqGameData->player;
   dqMap_t* oldMap = dqGameData_GetCurrentMap();
   dqMapTile_t* oldTile = dqMap_GetTileFromPosition( oldMap, &( player->centerPosition ) );
   dqMap_t* newMap = &( dqGameData->maps[newMapIndex] );
   dqMapTile_t* newTile;

   dqGameData->currentMapIndex = newMapIndex;

   newColumn = newTileIndex % newMap->columns;
   newRow = newTileIndex / newMap->columns;

   player->hitBoxPosition.x = newColumn * dqGameConfig->mapTileSize;
   player->hitBoxPosition.y = newRow * dqGameConfig->mapTileSize;

   player->centerPosition.x = player->hitBoxPosition.x + ( player->hitBoxSize.x / 2 );
   player->centerPosition.y = player->hitBoxPosition.y + ( player->hitBoxSize.y / 2 );

   if ( oldTile->hasEntranceDirection )
   {
      player->direction = oldTile->entranceDirection;
   }

   // don't check for encounters right away
   newTile = dqMap_GetTileFromPosition( newMap, &( player->centerPosition ) );
   newMap->playerTileCache = newTile;
}

void dqMap_CheckEncounter()
{
   unsigned int encounterValue;
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile = dqMap_GetTileFromPosition( map, &( dqGameData->player->centerPosition ));

   if ( tile != map->playerTileCache )
   {
      map->playerTileCache = tile;
      encounterValue = dqRandom_Percent();

      if ( encounterValue < tile->encounterRate )
      {
         dqEventQueue_Push( dqEventEncounter, 0 );
      }
   }
}
