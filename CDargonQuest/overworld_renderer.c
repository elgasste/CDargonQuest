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
   sfVector2f tileSize = { dqRenderConfig->tileSize, dqRenderConfig->tileSize };

   dqOverworldRenderer = (dqOverworldRenderer_t*)malloc( sizeof( dqOverworldRenderer_t ) );
   CHECK_MALLOC( dqOverworldRenderer )

   dqOverworldRenderer->darkTile = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->darkTile, tileSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->darkTile, sfColor_fromRGB( 96, 96, 96 ) );

   dqOverworldRenderer->lightTile = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->lightTile, tileSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->lightTile, sfColor_fromRGB( 224, 224, 224 ) );
}

void dqOverworldRenderer_Cleanup()
{
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
   float tileOffsetX, tileOffsetY;
   unsigned int startTileColumn, startTileRow, endTileColumn, endTileRow, column, row, i, j;
   dqMap_t* map = &( dqGameData->maps[0] );
   dqMapTile_t* tile;
   sfRectangleShape* rect;

   // TODO: consider the cases where the whole map fits in the view either horizontally or vertically.

   viewOffset->x = dqGameData->player->centerPosition.x - ( dqRenderConfig->screenWidth / 2 );

   if ( viewOffset->x < 0 )
   {
      viewOffset->x = 0;
   }
   else if ( ( viewOffset->x + dqRenderConfig->screenWidth ) >= map->width )
   {
      viewOffset->x = map->width - dqRenderConfig->screenWidth;
   }

   viewOffset->y = dqGameData->player->centerPosition.y - ( dqRenderConfig->screenHeight / 2 );

   if ( viewOffset->y < 0 )
   {
      viewOffset->y = 0;
   }
   else if ( ( viewOffset->y + dqRenderConfig->screenHeight ) >= map->height )
   {
      viewOffset->y = map->height - dqRenderConfig->screenHeight;
   }

   tileOffsetX = (float)( (unsigned int)viewOffset->x % (unsigned int)dqRenderConfig->tileSize );
   tileOffsetY = (float)( (unsigned int)viewOffset->y % (unsigned int)dqRenderConfig->tileSize );

   startTileColumn = (unsigned int)( viewOffset->x / dqRenderConfig->tileSize );
   startTileRow = (unsigned int)( viewOffset->y / dqRenderConfig->tileSize );

   endTileColumn = (unsigned int)( ( viewOffset->x + dqRenderConfig->screenWidth ) / dqRenderConfig->tileSize );
   endTileRow = (unsigned int)( ( viewOffset->y + dqRenderConfig->screenHeight ) / dqRenderConfig->tileSize );

   for ( i = 0, row = startTileRow; row <= endTileRow; row++, i++ )
   {
      for ( j = 0, column = startTileColumn; column <= endTileColumn; column++, j++ )
      {
         tile = dqMap_GetTile( map, column, row );
         rect = tile->tileId == 0 ? dqOverworldRenderer->darkTile : dqOverworldRenderer->lightTile;

         dqOverworldRenderer->tilePosition.x = ( j * dqRenderConfig->tileSize ) - tileOffsetX;
         dqOverworldRenderer->tilePosition.y = ( i * dqRenderConfig->tileSize ) - tileOffsetY;

         sfRectangleShape_setPosition( rect, dqOverworldRenderer->tilePosition );
         dqWindow_DrawRectangleShape( rect );
      }
   }
}

void dqOverworldRenderer_RenderEntities()
{
   dqEntitySprite_t* playerSprite = dqRenderData->playerSprite;
   sfVector2f position = {
      playerSprite->entity->hitBoxPosition.x - dqOverworldRenderer->viewOffset.x,
      playerSprite->entity->hitBoxPosition.y - dqOverworldRenderer->viewOffset.y
   };

   sfSprite_setPosition( playerSprite->sprite, position );
   dqWindow_DrawEntitySprite( dqRenderData->playerSprite );
}
