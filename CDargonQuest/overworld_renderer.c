#include "overworld_renderer.h"
#include "render_config.h"
#include "game_data.h"
#include "entity.h"
#include "map.h"
#include "map_tile.h"
#include "window.h"

void dqOverworldRenderer_Init()
{
   sfVector2f tileSize = { dqRenderConfig->tileSize, dqRenderConfig->tileSize };

   dqOverworldRenderer = (dqOverworldRenderer_t*)malloc( sizeof( dqOverworldRenderer_t ) );

#pragma warning ( suppress:6011 )
   dqOverworldRenderer->darkTile = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->darkTile, tileSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->darkTile, sfColor_fromRGB( 96, 96, 96 ) );

   dqOverworldRenderer->lightTile = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->lightTile, tileSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->lightTile, sfColor_fromRGB( 224, 224, 224 ) );

   dqOverworldRenderer->entityRect = sfRectangleShape_create();
   sfRectangleShape_setSize( dqOverworldRenderer->entityRect, dqGameData->player->hitBoxSize );
   sfRectangleShape_setFillColor( dqOverworldRenderer->entityRect, sfBlue );
}

void dqOverworldRenderer_Cleanup()
{
   sfRectangleShape_destroy( dqOverworldRenderer->entityRect );
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
   unsigned int i = 0, col = 0, row = 0;
   dqMap_t* map = &( dqGameData->maps[0] );
   dqMapTile_t* tile;
   sfRectangleShape* rect;

   for ( ; i < map->tileCount; i++ )
   {
      tile = &( map->tiles[i] );
      rect = tile->tileId == 0 ? dqOverworldRenderer->darkTile : dqOverworldRenderer->lightTile;

      dqOverworldRenderer->tilePosition.x = col * dqRenderConfig->tileSize;
      dqOverworldRenderer->tilePosition.y = row * dqRenderConfig->tileSize;

      sfRectangleShape_setPosition( rect, dqOverworldRenderer->tilePosition );
      dqWindow_DrawRectangleShape( rect );

      col++;

      if ( col >= map->width )
      {
         col = 0;
         row++;
      }
   }
}

void dqOverworldRenderer_RenderEntities()
{
   sfRectangleShape_setPosition( dqOverworldRenderer->entityRect, dqGameData->player->hitBoxPosition );
   dqWindow_DrawRectangleShape( dqOverworldRenderer->entityRect );
}
