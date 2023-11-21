#include "map.h"
#include "map_tile.h"
#include "game_config.h"
#include "game_data.h"
#include "player.h"
#include "entity_overworld_state.h"
#include "entity_sprite.h"
#include "event_queue.h"
#include "random.h"
#include "math_util.h"

dqMapTile_t* dqMap_GetTileFromCoordinates( dqMap_t* map, unsigned int column, unsigned int row )
{
   unsigned int tileIndex = dqMathUtil_IndexFromCoordinates( column, row, map->columns );
   return &( map->tiles[tileIndex] );
}

dqMapTile_t* dqMap_GetTileFromPosition( dqMap_t* map, sfVector2f* pos )
{
   unsigned int column = (unsigned int)( pos->x / dqGameConfig->mapTileSize );
   unsigned int row = (unsigned int)( pos->y / dqGameConfig->mapTileSize );

   unsigned int tileIndex = dqMathUtil_IndexFromCoordinates( column, row, map->columns );
   return &( map->tiles[tileIndex] );
}

dqMapTile_t* dqMap_GetCurrentTile()
{
   return dqMap_GetTileFromPosition( dqGameData_GetCurrentMap(), &( dqGameData->player->overworldState->centerPosition ) );
}

void dqMap_CheckSwap()
{
   dqMapTile_t* tile;

   if ( !dqGameConfig->noClipCheat )
   {
      tile = dqMap_GetCurrentTile();

      if ( tile->isExit )
      {
         dqEventQueue_Push( dqEventSwapMap, 2, (int)tile->exitMapIndex, (int)tile->entranceTileIndex );
      }  
   }
}

void dqMap_Swap( unsigned int newMapIndex, unsigned int newTileIndex )
{
   unsigned int newColumn, newRow;
   dqEntityOverworldState_t* playerState = dqGameData->player->overworldState;
   dqMapTile_t* oldTile = dqMap_GetCurrentTile();
   dqMap_t* newMap = &( dqGameData->maps[newMapIndex] );
   dqMapTile_t* newTile;

   dqGameData->currentMapIndex = newMapIndex;

   dqMathUtil_CoordinatesFromIndex( newTileIndex, newMap->columns, &newColumn, &newRow );

   playerState->hitBoxPosition.x = newColumn * dqGameConfig->mapTileSize;
   playerState->hitBoxPosition.y = newRow * dqGameConfig->mapTileSize;

   playerState->centerPosition.x = playerState->hitBoxPosition.x + ( playerState->hitBoxSize.x / 2 );
   playerState->centerPosition.y = playerState->hitBoxPosition.y + ( playerState->hitBoxSize.y / 2 );

   playerState->velocityX = 0;
   playerState->velocityY = 0;

   if ( oldTile->hasEntranceDirection )
   {
      playerState->direction = oldTile->entranceDirection;
   }

   dqEntitySprite_Tick( dqGameData->player->entitySprite );

   // don't check for encounters right away
   newTile = dqMap_GetTileFromPosition( newMap, &( playerState->centerPosition ) );
   newMap->playerTileCache = newTile;
}

void dqMap_CheckEncounter()
{
   unsigned int encounterValue;
   dqMap_t* map;
   dqMapTile_t* tile;

   if ( !dqGameConfig->noClipCheat && !dqGameConfig->invisibleCheat )
   {
      map = dqGameData_GetCurrentMap();
      tile = dqMap_GetCurrentTile();

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
}
