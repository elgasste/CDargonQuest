#include "physics.h"
#include "clock.h"
#include "game_config.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"
#include "entity_overworld_state.h"
#include "player.h"

static void dqPhysics_ClipHorizontal( dqEntityOverworldState_t* entityOverworldState,
                                      unsigned int prevLeftColumn, unsigned int prevRightColumn );
static void dqPhysics_ClipVertical( dqEntityOverworldState_t* entityOverworldState,
                                    unsigned int prevTopRow, unsigned int prevBottomRow );

void dqPhysics_MoveEntity( dqEntityOverworldState_t* entityOverworldState )
{
   unsigned int leftColumn, rightColumn, topRow, bottomRow;
   sfBool clip = entityOverworldState != dqGameData->player->overworldState || !dqGameConfig->noClipCheat;

   if ( entityOverworldState->velocityX != 0 )
   {
      leftColumn = (unsigned int)( entityOverworldState->hitBoxPosition.x / dqGameConfig->mapTileSize );
      rightColumn = (unsigned int)( ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) / dqGameConfig->mapTileSize );

      entityOverworldState->hitBoxPosition.x += entityOverworldState->velocityX * dqClock->lastFrameSeconds;
      entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );

      if ( clip )
      {
         dqPhysics_ClipHorizontal( entityOverworldState, leftColumn, rightColumn );
      }
   }

   if ( entityOverworldState->velocityY != 0 )
   {
      topRow = (unsigned int)( entityOverworldState->hitBoxPosition.y / dqGameConfig->mapTileSize );
      bottomRow = (unsigned int)( ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y ) / dqGameConfig->mapTileSize );

      entityOverworldState->hitBoxPosition.y += ( entityOverworldState->velocityY * dqClock->lastFrameSeconds );
      entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );

      if ( clip )
      {
         dqPhysics_ClipVertical( entityOverworldState, topRow, bottomRow );
      }
   }
}

void dqPhysics_DecelerateEntity( dqEntityOverworldState_t* entityOverworldState )
{
   // TODO: maybe have deceleration rates?
   entityOverworldState->velocityX = 0;
   entityOverworldState->velocityY = 0;
}

static void dqPhysics_ClipHorizontal( dqEntityOverworldState_t* entityOverworldState,
                                      unsigned int prevLeftColumn, unsigned int prevRightColumn )
{
   unsigned int newLeftColumn, newRightColumn, i;
   unsigned int topRow = (unsigned int)( entityOverworldState->hitBoxPosition.y / dqGameConfig->mapTileSize );
   unsigned int bottomRow = (unsigned int)( ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y ) / dqGameConfig->mapTileSize );
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile;

   if ( entityOverworldState->hitBoxPosition.x < 0 )
   {
      entityOverworldState->hitBoxPosition.x = 0;
      entityOverworldState->centerPosition.x = entityOverworldState->hitBoxSize.x / 2;
   }
   else if ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x >= map->size.x )
   {
      entityOverworldState->hitBoxPosition.x = map->size.x - entityOverworldState->hitBoxSize.x - COLLISION_ADJUSTMENT;
      entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
   }
   else
   {
      newLeftColumn = (unsigned int)( entityOverworldState->hitBoxPosition.x / dqGameConfig->mapTileSize );
      newRightColumn = (unsigned int)( ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) / dqGameConfig->mapTileSize );

      if ( newLeftColumn < prevLeftColumn )
      {
         for ( i = topRow; i <= bottomRow; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, newLeftColumn, i );

            if ( !tile->isPassable )
            {
               entityOverworldState->hitBoxPosition.x = prevLeftColumn * dqGameConfig->mapTileSize;
               entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
               break;
            }
         }
      }
      else if ( newRightColumn > prevRightColumn )
      {
         for ( i = topRow; i <= bottomRow; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, newRightColumn, i );

            if ( !tile->isPassable )
            {
               entityOverworldState->hitBoxPosition.x = ( newRightColumn * dqGameConfig->mapTileSize ) - entityOverworldState->hitBoxSize.x - COLLISION_ADJUSTMENT;
               entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
               break;
            }
         }
      }
   }
}

static void dqPhysics_ClipVertical( dqEntityOverworldState_t* entityOverworldState,
                                    unsigned int prevTopRow, unsigned int prevBottomRow )
{
   unsigned int newTopRow, newBottomRow, i;
   unsigned int leftColumn = (unsigned int)( entityOverworldState->hitBoxPosition.x / dqGameConfig->mapTileSize );
   unsigned int rightColumn = (unsigned int)( ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) / dqGameConfig->mapTileSize );
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile;

   if ( entityOverworldState->hitBoxPosition.y < 0 )
   {
      entityOverworldState->hitBoxPosition.y = 0;
      entityOverworldState->centerPosition.y = entityOverworldState->hitBoxSize.y / 2;
   }
   else if ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y >= map->size.y )
   {
      entityOverworldState->hitBoxPosition.y = map->size.y - entityOverworldState->hitBoxSize.y - COLLISION_ADJUSTMENT;
      entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
   }
   else
   {
      newTopRow = (unsigned int)( entityOverworldState->hitBoxPosition.y / dqGameConfig->mapTileSize );
      newBottomRow = (unsigned int)( ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y ) / dqGameConfig->mapTileSize );

      if ( newTopRow < prevTopRow )
      {
         for ( i = leftColumn; i <= rightColumn; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, i, newTopRow );

            if ( !tile->isPassable )
            {
               entityOverworldState->hitBoxPosition.y = prevTopRow * dqGameConfig->mapTileSize;
               entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
               break;
            }
         }
      }
      else if ( newBottomRow > prevBottomRow )
      {
         for ( i = leftColumn; i <= rightColumn; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, i, newBottomRow );

            if ( !tile->isPassable )
            {
               entityOverworldState->hitBoxPosition.y = ( newBottomRow * dqGameConfig->mapTileSize ) - entityOverworldState->hitBoxSize.y - COLLISION_ADJUSTMENT;
               entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
               break;
            }
         }
      }
   }
}
