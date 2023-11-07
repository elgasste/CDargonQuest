#include "physics.h"
#include "entity.h"
#include "clock.h"
#include "game_config.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"

static void dqPhysics_ClipHorizontal( dqEntity_t* entity,
                                      unsigned int prevLeftColumn, unsigned int prevRightColumn )
{
   unsigned int newLeftColumn, newRightColumn, i;
   unsigned int topRow = (unsigned int)( entity->hitBoxPosition.y / dqGameConfig->mapTileSize );
   unsigned int bottomRow = (unsigned int)( ( entity->hitBoxPosition.y + entity->hitBoxSize.y ) / dqGameConfig->mapTileSize );
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile;

   if ( entity->hitBoxPosition.x < 0 )
   {
      entity->hitBoxPosition.x = 0;
      entity->centerPosition.x = entity->hitBoxSize.x / 2;
   }
   else if ( entity->hitBoxPosition.x + entity->hitBoxSize.x >= map->size.x )
   {
      entity->hitBoxPosition.x = map->size.x - entity->hitBoxSize.x - COLLISION_ADJUSTMENT;
      entity->centerPosition.x = entity->hitBoxPosition.x + ( entity->hitBoxSize.x / 2 );
   }
   else
   {
      newLeftColumn = (unsigned int)( entity->hitBoxPosition.x / dqGameConfig->mapTileSize );
      newRightColumn = (unsigned int)( ( entity->hitBoxPosition.x + entity->hitBoxSize.x ) / dqGameConfig->mapTileSize );

      if ( newLeftColumn < prevLeftColumn )
      {
         for ( i = topRow; i <= bottomRow; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, newLeftColumn, i );

            if ( !tile->isPassable )
            {
               entity->hitBoxPosition.x = prevLeftColumn * dqGameConfig->mapTileSize;
               entity->centerPosition.x = entity->hitBoxPosition.x + ( entity->hitBoxSize.x / 2 );
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
               entity->hitBoxPosition.x = ( newRightColumn * dqGameConfig->mapTileSize ) - entity->hitBoxSize.x - COLLISION_ADJUSTMENT;
               entity->centerPosition.x = entity->hitBoxPosition.x + ( entity->hitBoxSize.x / 2 );
               break;
            }
         }
      }
   }
}

static void dqPhysics_ClipVertical( dqEntity_t* entity,
                                    unsigned int prevTopRow, unsigned int prevBottomRow )
{
   unsigned int newTopRow, newBottomRow, i;
   unsigned int leftColumn = (unsigned int)( entity->hitBoxPosition.x / dqGameConfig->mapTileSize );
   unsigned int rightColumn = (unsigned int)( ( entity->hitBoxPosition.x + entity->hitBoxSize.x ) / dqGameConfig->mapTileSize );
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile;

   if ( entity->hitBoxPosition.y < 0 )
   {
      entity->hitBoxPosition.y = 0;
      entity->centerPosition.y = entity->hitBoxSize.y / 2;
   }
   else if ( entity->hitBoxPosition.y + entity->hitBoxSize.y >= map->size.y )
   {
      entity->hitBoxPosition.y = map->size.y - entity->hitBoxSize.y - COLLISION_ADJUSTMENT;
      entity->centerPosition.y = entity->hitBoxPosition.y + ( entity->hitBoxSize.y / 2 );
   }
   else
   {
      newTopRow = (unsigned int)( entity->hitBoxPosition.y / dqGameConfig->mapTileSize );
      newBottomRow = (unsigned int)( ( entity->hitBoxPosition.y + entity->hitBoxSize.y ) / dqGameConfig->mapTileSize );

      if ( newTopRow < prevTopRow )
      {
         for ( i = leftColumn; i <= rightColumn; i++ )
         {
            tile = dqMap_GetTileFromCoordinates( map, i, newTopRow );

            if ( !tile->isPassable )
            {
               entity->hitBoxPosition.y = prevTopRow * dqGameConfig->mapTileSize;
               entity->centerPosition.y = entity->hitBoxPosition.y + ( entity->hitBoxSize.y / 2 );
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
               entity->hitBoxPosition.y = ( newBottomRow * dqGameConfig->mapTileSize ) - entity->hitBoxSize.y - COLLISION_ADJUSTMENT;
               entity->centerPosition.y = entity->hitBoxPosition.y + ( entity->hitBoxSize.y / 2 );
               break;
            }
         }
      }
   }
}

void dqPhysics_MoveEntity( dqEntity_t* entity )
{
   unsigned int leftColumn, rightColumn, topRow, bottomRow;
   sfBool clip = entity != dqGameData->player || !dqGameConfig->noClipCheat;

   if ( entity->velocityX != 0 )
   {
      leftColumn = (unsigned int)( entity->hitBoxPosition.x / dqGameConfig->mapTileSize );
      rightColumn = (unsigned int)( ( entity->hitBoxPosition.x + entity->hitBoxSize.x ) / dqGameConfig->mapTileSize );

      entity->hitBoxPosition.x += entity->velocityX * dqClock->lastFrameSeconds;
      entity->centerPosition.x = entity->hitBoxPosition.x + ( entity->hitBoxSize.x / 2 );

      if ( clip )
      {
         dqPhysics_ClipHorizontal( entity, leftColumn, rightColumn );
      }
   }

   if ( entity->velocityY != 0 )
   {
      topRow = (unsigned int)( entity->hitBoxPosition.y / dqGameConfig->mapTileSize );
      bottomRow = (unsigned int)( ( entity->hitBoxPosition.y + entity->hitBoxSize.y ) / dqGameConfig->mapTileSize );

      entity->hitBoxPosition.y += ( entity->velocityY * dqClock->lastFrameSeconds );
      entity->centerPosition.y = entity->hitBoxPosition.y + ( entity->hitBoxSize.y / 2 );

      if ( clip )
      {
         dqPhysics_ClipVertical( entity, topRow, bottomRow );
      }
   }
}

void dqPhysics_DecelerateEntity( dqEntity_t* entity )
{
   // TODO: maybe have deceleration rates?
   entity->velocityX = 0;
   entity->velocityY = 0;
}
