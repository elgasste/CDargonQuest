#include "overworld_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "game_data.h"
#include "entity.h"
#include "map.h"
#include "map_tile.h"
#include "window.h"

void dqOverworldRenderer_Init()
{
   int i;

   sfVector2f tileSize = { dqRenderConfig->tileSize, dqRenderConfig->tileSize };

   sfVector2f occlusionSize0 = { dqRenderConfig->overworldViewOffset.x, dqRenderConfig->screenHeight };
   sfVector2f occlusionPos0 = { 0, 0 };

   sfVector2f occlusionSize1 = { dqRenderConfig->screenWidth - occlusionSize0.x, dqRenderConfig->overworldViewOffset.y };
   sfVector2f occlusionPos1 = { occlusionSize0.x, 0 };

   sfVector2f occlusionSize2 = {
      dqRenderConfig->screenWidth - occlusionSize0.x - dqRenderConfig->overworldViewSize.x,
      dqRenderConfig->screenHeight - occlusionSize1.y };
   sfVector2f occlusionPos2 = { occlusionSize0.x + dqRenderConfig->overworldViewSize.x, occlusionSize1.y };

   sfVector2f occlusionSize3 = {
      dqRenderConfig->screenWidth - occlusionSize0.x - occlusionSize2.x,
      dqRenderConfig->screenHeight - occlusionSize1.y - dqRenderConfig->overworldViewSize.y };
   sfVector2f occlusionPos3 = { occlusionSize0.x, occlusionSize1.y + dqRenderConfig->overworldViewSize.y };

   dqOverworldRenderer = (dqOverworldRenderer_t*)malloc( sizeof( dqOverworldRenderer_t ) );
   CHECK_MALLOC( dqOverworldRenderer )

   dqOverworldRenderer->darkTile = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->darkTile, tileSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->darkTile, sfColor_fromRGB( 96, 96, 96 ) );

   dqOverworldRenderer->lightTile = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->lightTile, tileSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->lightTile, sfColor_fromRGB( 224, 224, 224 ) );

   for ( i = 0; i < 4; i++ )
   {
      dqOverworldRenderer->occlusions[i] = sfRectangleShape_create();
      sfRectangleShape_setFillColor( dqOverworldRenderer->occlusions[i], dqRenderConfig->windowClearColor );
   }

   sfRectangleShape_setSize( dqOverworldRenderer->occlusions[0], occlusionSize0 );
   sfRectangleShape_setPosition( dqOverworldRenderer->occlusions[0], occlusionPos0 );

   sfRectangleShape_setSize( dqOverworldRenderer->occlusions[1], occlusionSize1 );
   sfRectangleShape_setPosition( dqOverworldRenderer->occlusions[1], occlusionPos1 );

   sfRectangleShape_setSize( dqOverworldRenderer->occlusions[2], occlusionSize2 );
   sfRectangleShape_setPosition( dqOverworldRenderer->occlusions[2], occlusionPos2 );

   sfRectangleShape_setSize( dqOverworldRenderer->occlusions[3], occlusionSize3 );
   sfRectangleShape_setPosition( dqOverworldRenderer->occlusions[3], occlusionPos3 );
}

void dqOverworldRenderer_Cleanup()
{
   int i;

   for ( i = 0; i < 4; i++ )
   {
      sfRectangleShape_destroy( dqOverworldRenderer->occlusions[i] );
   }

   sfRectangleShape_destroy( dqOverworldRenderer->darkTile );
   sfRectangleShape_destroy( dqOverworldRenderer->lightTile );

   SAFE_DELETE( dqOverworldRenderer );
}

void dqOverworldRenderer_Render()
{
   dqOverworldRenderer_RenderMap();
   dqOverworldRenderer_RenderEntities();
}

void dqOverworldRenderer_RenderMap()
{
   sfVector2f* viewOffset = &( dqOverworldRenderer->viewOffset );
   sfVector2f* sideOffset = &( dqOverworldRenderer->sideOffset );
   float tileOffsetX, tileOffsetY;
   unsigned int startTileColumn, startTileRow, endTileColumn, endTileRow, column, row, i, j;
   dqMap_t* map = &( dqGameData->maps[0] );
   dqMapTile_t* tile;
   sfRectangleShape* rect;

   if ( map->size.x < dqRenderConfig->overworldViewSize.x )
   {
      viewOffset->x = 0;
      sideOffset->x = ( dqRenderConfig->overworldViewSize.x / 2 ) - ( map->size.x / 2 );
      tileOffsetX = 0;
      startTileColumn = 0;
      endTileColumn = map->columns - 1;
   }
   else
   {
      viewOffset->x = dqGameData->player->centerPosition.x - ( dqRenderConfig->overworldViewSize.x / 2 );
      sideOffset->x = 0;

      if ( viewOffset->x < 0 )
      {
         viewOffset->x = 0;
      }
      else if ( ( viewOffset->x + dqRenderConfig->overworldViewSize.x ) >= map->size.x )
      {
         viewOffset->x = map->size.x - dqRenderConfig->overworldViewSize.x;
      }

      tileOffsetX = (float)( (unsigned int)viewOffset->x % (unsigned int)dqRenderConfig->tileSize );
      startTileColumn = (unsigned int)( viewOffset->x / dqRenderConfig->tileSize );
      endTileColumn = (unsigned int)( ( viewOffset->x + dqRenderConfig->overworldViewSize.x ) / dqRenderConfig->tileSize );
   }

   if ( map->size.y < dqRenderConfig->overworldViewSize.y )
   {
      viewOffset->y = 0;
      sideOffset->y = ( dqRenderConfig->overworldViewSize.y / 2 ) - ( map->size.y / 2 );
      tileOffsetY = 0;
      startTileRow = 0;
      endTileRow = map->rows - 1;
   }
   else
   {
      viewOffset->y = dqGameData->player->centerPosition.y - ( dqRenderConfig->overworldViewSize.y / 2 );
      sideOffset->y = 0;

      if ( viewOffset->y < 0 )
      {
         viewOffset->y = 0;
      }
      else if ( ( viewOffset->y + dqRenderConfig->overworldViewSize.y ) >= map->size.y )
      {
         viewOffset->y = map->size.y - dqRenderConfig->overworldViewSize.y;
      }

      tileOffsetY = (float)( (unsigned int)viewOffset->y % (unsigned int)dqRenderConfig->tileSize );
      startTileRow = (unsigned int)( viewOffset->y / dqRenderConfig->tileSize );
      endTileRow = (unsigned int)( ( viewOffset->y + dqRenderConfig->overworldViewSize.y ) / dqRenderConfig->tileSize );
   }

   for ( i = 0, row = startTileRow; row <= endTileRow; row++, i++ )
   {
      for ( j = 0, column = startTileColumn; column <= endTileColumn; column++, j++ )
      {
         tile = dqMap_GetTile( map, column, row );
         rect = tile->tileId == 0 ? dqOverworldRenderer->darkTile : dqOverworldRenderer->lightTile;

         dqOverworldRenderer->tilePosition.x = ( j * dqRenderConfig->tileSize ) - tileOffsetX + sideOffset->x + dqRenderConfig->overworldViewOffset.x;
         dqOverworldRenderer->tilePosition.y = ( i * dqRenderConfig->tileSize ) - tileOffsetY + sideOffset->y + dqRenderConfig->overworldViewOffset.y;

         sfRectangleShape_setPosition( rect, dqOverworldRenderer->tilePosition );
         dqWindow_DrawRectangleShape( rect );
      }
   }

   for ( i = 0; i < 4; i++ )
   {
      dqWindow_DrawRectangleShape( dqOverworldRenderer->occlusions[i] );
   }
}

void dqOverworldRenderer_RenderEntities()
{
   dqEntitySprite_t* playerSprite = dqRenderData->playerSprite;
   sfVector2f position = {
      playerSprite->entity->hitBoxPosition.x - dqOverworldRenderer->viewOffset.x + dqOverworldRenderer->sideOffset.x + dqRenderConfig->overworldViewOffset.x,
      playerSprite->entity->hitBoxPosition.y - dqOverworldRenderer->viewOffset.y + dqOverworldRenderer->sideOffset.y + dqRenderConfig->overworldViewOffset.y
   };

   sfSprite_setPosition( playerSprite->sprite, position );
   dqWindow_DrawEntitySprite( dqRenderData->playerSprite );
}
