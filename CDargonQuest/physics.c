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
   dqMap_t* map = dqGameData_GetCurrentMap();
   sfBool clip = entityOverworldState != dqGameData->player->overworldState || !dqGameConfig->noClipCheat;

   if ( entityOverworldState->velocityX != 0 )
   {
      if ( entityOverworldState->hitBoxPosition.x < 0 )
      {
         leftColumn = map->columns + (unsigned int)( entityOverworldState->hitBoxPosition.x / dqGameConfig->mapTileSize ) - 1;
      }
      else
      {
         leftColumn = (unsigned int)( entityOverworldState->hitBoxPosition.x / dqGameConfig->mapTileSize );
      }

      if ( entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x ) >= map->size.x )
      {
         rightColumn = (unsigned int)( ( ( entityOverworldState->hitBoxPosition.x - map->size.x ) + entityOverworldState->hitBoxSize.x ) / dqGameConfig->mapTileSize );
      }
      else
      {
         rightColumn = (unsigned int)( ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) / dqGameConfig->mapTileSize );
      }

      entityOverworldState->hitBoxPosition.x += entityOverworldState->velocityX * dqClock->lastFrameSeconds;
      entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );

      // make sure the center point is always in range
      if ( entityOverworldState->centerPosition.x < 0 )
      {
         entityOverworldState->centerPosition.x = map->size.x + entityOverworldState->centerPosition.x;
         entityOverworldState->hitBoxPosition.x = entityOverworldState->centerPosition.x - ( entityOverworldState->hitBoxSize.x / 2 );
      }
      else if ( entityOverworldState->centerPosition.x >= map->size.x )
      {
         entityOverworldState->centerPosition.x -= map->size.x;
         entityOverworldState->hitBoxPosition.x = entityOverworldState->centerPosition.x - ( entityOverworldState->hitBoxSize.x / 2 );
      }

      if ( clip )
      {
         dqPhysics_ClipHorizontal( entityOverworldState, leftColumn, rightColumn );
      }
   }

   if ( entityOverworldState->velocityY != 0 )
   {
      if ( entityOverworldState->hitBoxPosition.y < 0 )
      {
         topRow = map->rows + (unsigned int)( entityOverworldState->hitBoxPosition.y / dqGameConfig->mapTileSize ) - 1;
      }
      else
      {
         topRow = (unsigned int)( entityOverworldState->hitBoxPosition.y / dqGameConfig->mapTileSize );
      }

      if ( entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y ) >= map->size.y )
      {
         bottomRow = (unsigned int)( ( ( entityOverworldState->hitBoxPosition.y - map->size.y ) + entityOverworldState->hitBoxSize.y ) / dqGameConfig->mapTileSize );
      }
      else
      {
         bottomRow = (unsigned int)( ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y ) / dqGameConfig->mapTileSize );
      }

      entityOverworldState->hitBoxPosition.y += ( entityOverworldState->velocityY * dqClock->lastFrameSeconds );
      entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );

      // make sure the center point is always in range
      if ( entityOverworldState->centerPosition.y < 0 )
      {
         entityOverworldState->centerPosition.y = map->size.y + entityOverworldState->centerPosition.y;
         entityOverworldState->hitBoxPosition.y = entityOverworldState->centerPosition.y - ( entityOverworldState->hitBoxSize.y / 2 );
      }
      else if ( entityOverworldState->centerPosition.y >= map->size.y )
      {
         entityOverworldState->centerPosition.y -= map->size.y;
         entityOverworldState->hitBoxPosition.y = entityOverworldState->centerPosition.y - ( entityOverworldState->hitBoxSize.y / 2 );
      }

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

   if ( !map->wrap && ( entityOverworldState->hitBoxPosition.x < 0 ) )
   {
      entityOverworldState->hitBoxPosition.x = 0;
      entityOverworldState->centerPosition.x = entityOverworldState->hitBoxSize.x / 2;
   }
   else if ( !map->wrap && ( ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) >= map->size.x ) )
   {
      entityOverworldState->hitBoxPosition.x = map->size.x - entityOverworldState->hitBoxSize.x - COLLISION_ADJUSTMENT;
      entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
   }
   else
   {
      newLeftColumn = entityOverworldState->hitBoxPosition.x < 0
         ? map->columns - 1
         : (unsigned int)( entityOverworldState->hitBoxPosition.x / dqGameConfig->mapTileSize );
      newRightColumn = ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) >= map->size.x
         ? 0
         : (unsigned int)( ( entityOverworldState->hitBoxPosition.x + entityOverworldState->hitBoxSize.x ) / dqGameConfig->mapTileSize );

      if ( newLeftColumn != prevLeftColumn )
      {
         for ( i = topRow; i <= bottomRow; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, newLeftColumn, i );

            if ( !tile->isPassable )
            {
               if ( newLeftColumn > prevLeftColumn )
               {
                  entityOverworldState->hitBoxPosition.x = COLLISION_ADJUSTMENT;
                  entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
               }
               else
               {
                  entityOverworldState->hitBoxPosition.x = prevLeftColumn * dqGameConfig->mapTileSize;
                  entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
               }

               break;
            }
         }
      }
      else if ( newRightColumn != prevRightColumn )
      {
         for ( i = topRow; i <= bottomRow; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, newRightColumn, i );

            if ( !tile->isPassable )
            {
               if ( newRightColumn < prevRightColumn )
               {
                  entityOverworldState->hitBoxPosition.x = map->size.x - entityOverworldState->hitBoxSize.x - COLLISION_ADJUSTMENT;
                  entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
               }
               else
               {
                  entityOverworldState->hitBoxPosition.x = ( newRightColumn * dqGameConfig->mapTileSize ) - entityOverworldState->hitBoxSize.x - COLLISION_ADJUSTMENT;
                  entityOverworldState->centerPosition.x = entityOverworldState->hitBoxPosition.x + ( entityOverworldState->hitBoxSize.x / 2 );
               }

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

   if ( !map->wrap && entityOverworldState->hitBoxPosition.y < 0 )
   {
      entityOverworldState->hitBoxPosition.y = 0;
      entityOverworldState->centerPosition.y = entityOverworldState->hitBoxSize.y / 2;
   }
   else if ( !map->wrap && entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y >= map->size.y )
   {
      entityOverworldState->hitBoxPosition.y = map->size.y - entityOverworldState->hitBoxSize.y - COLLISION_ADJUSTMENT;
      entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
   }
   else
   {
      newTopRow = entityOverworldState->hitBoxPosition.y < 0
         ? map->rows - 1
         : (unsigned int)( entityOverworldState->hitBoxPosition.y / dqGameConfig->mapTileSize );
      newBottomRow = ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y ) >= map->size.y
         ? 0
         :(unsigned int)( ( entityOverworldState->hitBoxPosition.y + entityOverworldState->hitBoxSize.y ) / dqGameConfig->mapTileSize );

      if ( newTopRow != prevTopRow )
      {
         for ( i = leftColumn; i <= rightColumn; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, i, newTopRow );

            if ( !tile->isPassable )
            {
               if ( newTopRow > prevTopRow )
               {
                  entityOverworldState->hitBoxPosition.y = COLLISION_ADJUSTMENT;
                  entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
               }
               else
               {
                  entityOverworldState->hitBoxPosition.y = prevTopRow * dqGameConfig->mapTileSize;
                  entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
               }

               break;
            }
         }
      }
      else if ( newBottomRow != prevBottomRow )
      {
         for ( i = leftColumn; i <= rightColumn; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, i, newBottomRow );

            if ( !tile->isPassable )
            {
               if ( newBottomRow < prevBottomRow )
               {
                  entityOverworldState->hitBoxPosition.y = map->size.y - entityOverworldState->hitBoxSize.y - COLLISION_ADJUSTMENT;
                  entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
               }
               else
               {
                  entityOverworldState->hitBoxPosition.y = ( newBottomRow * dqGameConfig->mapTileSize ) - entityOverworldState->hitBoxSize.y - COLLISION_ADJUSTMENT;
                  entityOverworldState->centerPosition.y = entityOverworldState->hitBoxPosition.y + ( entityOverworldState->hitBoxSize.y / 2 );
               }

               break;
            }
         }
      }
   }
}
