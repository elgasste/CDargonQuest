#include "overworld_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "game_config.h"
#include "game_data.h"
#include "player.h"
#include "entity_overworld_state.h"
#include "map.h"
#include "map_tile.h"
#include "window.h"
#include "math_util.h"

void dqOverworldRenderer_Init()
{
   int i;

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

   sfVector2f tileSize = { dqGameConfig->mapTileSize, dqGameConfig->mapTileSize };

   dqOverworldRenderer = (dqOverworldRenderer_t*)dqMalloc( sizeof( dqOverworldRenderer_t ), sfTrue );

   dqOverworldRenderer->tileSprite = sfSprite_create();
   sfSprite_setTexture( dqOverworldRenderer->tileSprite, dqRenderData->overworldTilesetTexture, sfFalse );
   dqOverworldRenderer->tileTextureRect.width = (int)dqGameConfig->mapTileSize;
   dqOverworldRenderer->tileTextureRect.height = (int)dqGameConfig->mapTileSize;

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

   dqOverworldRenderer->passableRect = sfRectangleShape_create();
   dqOverworldRenderer->impassableRect = sfRectangleShape_create();
   dqOverworldRenderer->mapSwapRect = sfRectangleShape_create();

   sfRectangleShape_setSize( dqOverworldRenderer->passableRect, tileSize );
   sfRectangleShape_setSize( dqOverworldRenderer->impassableRect, tileSize );
   sfRectangleShape_setSize( dqOverworldRenderer->mapSwapRect, tileSize );

   sfRectangleShape_setFillColor( dqOverworldRenderer->passableRect, dqRenderConfig->passableOverlayColor );
   sfRectangleShape_setFillColor( dqOverworldRenderer->impassableRect, dqRenderConfig->impassableOverlayColor );
   sfRectangleShape_setFillColor( dqOverworldRenderer->mapSwapRect, dqRenderConfig->mapSwapOverlayColor );

   dqOverworldRenderer->cheatFont = sfFont_createFromFile( dqRenderConfig->cheatFontFilePath );
   dqOverworldRenderer->cheatText = sfText_create();
   sfText_setFont( dqOverworldRenderer->cheatText, dqOverworldRenderer->cheatFont );
   sfText_setCharacterSize( dqOverworldRenderer->cheatText, dqRenderConfig->cheatFontSize );
   sfText_setScale( dqOverworldRenderer->cheatText, dqRenderConfig->cheatFontScale );
   sfText_setLetterSpacing( dqOverworldRenderer->cheatText, dqRenderConfig->cheatLetterSpacing );
   sfText_setFillColor( dqOverworldRenderer->cheatText, dqRenderConfig->cheatFontColor );
}

void dqOverworldRenderer_Cleanup()
{
   int i;

   sfText_destroy( dqOverworldRenderer->cheatText );
   sfFont_destroy( dqOverworldRenderer->cheatFont );

   sfRectangleShape_destroy( dqOverworldRenderer->passableRect );
   sfRectangleShape_destroy( dqOverworldRenderer->impassableRect );
   sfRectangleShape_destroy( dqOverworldRenderer->mapSwapRect );

   for ( i = 0; i < 4; i++ )
   {
      sfRectangleShape_destroy( dqOverworldRenderer->occlusions[i] );
   }

   sfSprite_destroy( dqOverworldRenderer->tileSprite );

   dqFree( dqOverworldRenderer, sizeof( dqOverworldRenderer_t ), sfTrue );
}

void dqOverworldRenderer_RenderMap()
{
   sfVector2f* viewOffset = &( dqOverworldRenderer->viewOffset );
   sfVector2f* sideOffset = &( dqOverworldRenderer->sideOffset );
   static sfVector2f tilePosition;
   static sfVector2f tileOffset;
   unsigned int startTileColumn, startTileRow, endTileColumn, endTileRow, column, row, i, j;
   dqMap_t* map = dqGameData_GetCurrentMap();
   dqMapTile_t* tile;

   if ( map->size.x < dqRenderConfig->overworldViewSize.x )
   {
      viewOffset->x = 0;
      sideOffset->x = ( dqRenderConfig->overworldViewSize.x / 2 ) - ( map->size.x / 2 );
      tileOffset.x = 0;
      startTileColumn = 0;
      endTileColumn = map->columns - 1;
   }
   else
   {
      viewOffset->x = dqGameData->player->overworldState->centerPosition.x - ( dqRenderConfig->overworldViewSize.x / 2 );
      sideOffset->x = 0;

      if ( viewOffset->x < 0 )
      {
         viewOffset->x = 0;
      }
      else if ( ( viewOffset->x + dqRenderConfig->overworldViewSize.x ) >= map->size.x )
      {
         viewOffset->x = map->size.x - dqRenderConfig->overworldViewSize.x;
      }

      startTileColumn = (unsigned int)( viewOffset->x / dqGameConfig->mapTileSize );
      endTileColumn = (unsigned int)( ( viewOffset->x + dqRenderConfig->overworldViewSize.x ) / dqGameConfig->mapTileSize );
      tileOffset.x = viewOffset->x - ( startTileColumn * dqGameConfig->mapTileSize );
   }

   if ( map->size.y < dqRenderConfig->overworldViewSize.y )
   {
      viewOffset->y = 0;
      sideOffset->y = ( dqRenderConfig->overworldViewSize.y / 2 ) - ( map->size.y / 2 );
      tileOffset.y = 0;
      startTileRow = 0;
      endTileRow = map->rows - 1;
   }
   else
   {
      viewOffset->y = dqGameData->player->overworldState->centerPosition.y - ( dqRenderConfig->overworldViewSize.y / 2 );
      sideOffset->y = 0;

      if ( viewOffset->y < 0 )
      {
         viewOffset->y = 0;
      }
      else if ( ( viewOffset->y + dqRenderConfig->overworldViewSize.y ) >= map->size.y )
      {
         viewOffset->y = map->size.y - dqRenderConfig->overworldViewSize.y;
      }

      startTileRow = (unsigned int)( viewOffset->y / dqGameConfig->mapTileSize );
      endTileRow = (unsigned int)( ( viewOffset->y + dqRenderConfig->overworldViewSize.y ) / dqGameConfig->mapTileSize );
      tileOffset.y = viewOffset->y - ( startTileRow * dqGameConfig->mapTileSize );
   }

   for ( i = 0, row = startTileRow; row <= endTileRow; row++, i++ )
   {
      for ( j = 0, column = startTileColumn; column <= endTileColumn; column++, j++ )
      {
         tile = dqMap_GetTileFromCoordinates( map, column, row );

         dqOverworldRenderer->tileTextureRect.left = (int)( ( tile->tileId % 16 ) * dqGameConfig->mapTileSize );
         dqOverworldRenderer->tileTextureRect.top = (int)( ( tile->tileId / 16 ) * dqGameConfig->mapTileSize );

         sfSprite_setTextureRect( dqOverworldRenderer->tileSprite, dqOverworldRenderer->tileTextureRect );

         tilePosition.x = ( j * dqGameConfig->mapTileSize ) - tileOffset.x + sideOffset->x + dqRenderConfig->overworldViewOffset.x;
         tilePosition.y = ( i * dqGameConfig->mapTileSize ) - tileOffset.y + sideOffset->y + dqRenderConfig->overworldViewOffset.y;
         
         sfSprite_setPosition( dqOverworldRenderer->tileSprite, tilePosition );
         dqWindow_DrawSprite( dqOverworldRenderer->tileSprite );

         if ( dqGameConfig->tileStatCheat )
         {
            if ( tile->isExit )
            {
               sfRectangleShape_setPosition( dqOverworldRenderer->mapSwapRect, tilePosition );
               dqWindow_DrawRectangleShape( dqOverworldRenderer->mapSwapRect );
            }
            else if ( tile->isPassable )
            {
               sfRectangleShape_setPosition( dqOverworldRenderer->passableRect, tilePosition );
               dqWindow_DrawRectangleShape( dqOverworldRenderer->passableRect );
            }
            else
            {
               sfRectangleShape_setPosition( dqOverworldRenderer->impassableRect, tilePosition );
               dqWindow_DrawRectangleShape( dqOverworldRenderer->impassableRect );
            }

            sprintf_s( dqOverworldRenderer->cheatChars, 64, "R:%d\nT:%d-%d", tile->encounterRate, tile->minEnemyTier, tile->maxEnemyTier );
            sfText_setString( dqOverworldRenderer->cheatText, dqOverworldRenderer->cheatChars );
            sfText_setPosition( dqOverworldRenderer->cheatText, tilePosition );
            dqWindow_DrawText( dqOverworldRenderer->cheatText );
         }
      }
   }

   for ( i = 0; i < 4; i++ )
   {
      dqWindow_DrawRectangleShape( dqOverworldRenderer->occlusions[i] );
   }
}

void dqOverworldRenderer_RenderEntities()
{
   static sfVector2f position;
   dqEntitySprite_t* playerSprite = dqRenderData->playerSprite;

   position.x = playerSprite->entityOverworldState->hitBoxPosition.x
      - playerSprite->hitBoxOffset.x
      - dqOverworldRenderer->viewOffset.x
      + dqOverworldRenderer->sideOffset.x
      + dqRenderConfig->overworldViewOffset.x;
   position.y = playerSprite->entityOverworldState->hitBoxPosition.y
      - playerSprite->hitBoxOffset.y
      - dqOverworldRenderer->viewOffset.y
      + dqOverworldRenderer->sideOffset.y
      + dqRenderConfig->overworldViewOffset.y;

   sfSprite_setPosition( playerSprite->sprite, position );
   dqWindow_DrawEntitySprite( dqRenderData->playerSprite );
}
