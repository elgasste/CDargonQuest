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

static void dqOverworldRenderer_RenderMapSection( dqMap_t* map, sfVector2f* tileOffset, sfVector2f* padding,
                                                  unsigned int startTileColumn, unsigned int endTileColumn,
                                                  unsigned int startTileRow, unsigned int endTileRow );
static void dqOverworldRenderer_RenderEntities( sfVector2f* viewOffset, sfVector2f* padding );

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

   dqOverworldRenderer->tileSprite = dqSprite_Create();
   sfSprite_setTexture( dqOverworldRenderer->tileSprite, dqRenderData->overworldTilesetTexture, sfFalse );
   dqOverworldRenderer->tileTextureRect.width = (int)dqGameConfig->mapTileSize;
   dqOverworldRenderer->tileTextureRect.height = (int)dqGameConfig->mapTileSize;

   for ( i = 0; i < 4; i++ )
   {
      dqOverworldRenderer->occlusions[i] = dqRectangleShape_Create();
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

   dqOverworldRenderer->passableRect = dqRectangleShape_Create();
   dqOverworldRenderer->impassableRect = dqRectangleShape_Create();
   dqOverworldRenderer->mapSwapRect = dqRectangleShape_Create();

   sfRectangleShape_setSize( dqOverworldRenderer->passableRect, tileSize );
   sfRectangleShape_setSize( dqOverworldRenderer->impassableRect, tileSize );
   sfRectangleShape_setSize( dqOverworldRenderer->mapSwapRect, tileSize );

   sfRectangleShape_setFillColor( dqOverworldRenderer->passableRect, dqRenderConfig->passableOverlayColor );
   sfRectangleShape_setFillColor( dqOverworldRenderer->impassableRect, dqRenderConfig->impassableOverlayColor );
   sfRectangleShape_setFillColor( dqOverworldRenderer->mapSwapRect, dqRenderConfig->mapSwapOverlayColor );

   dqOverworldRenderer->cheatFont = dqFont_CreateFromFile( dqRenderConfig->cheatFontFilePath );
   dqOverworldRenderer->cheatText = dqText_Create();
   sfText_setFont( dqOverworldRenderer->cheatText, dqOverworldRenderer->cheatFont );
   sfText_setCharacterSize( dqOverworldRenderer->cheatText, dqRenderConfig->cheatFontSize );
   sfText_setScale( dqOverworldRenderer->cheatText, dqRenderConfig->cheatFontScale );
   sfText_setLetterSpacing( dqOverworldRenderer->cheatText, dqRenderConfig->cheatLetterSpacing );
   sfText_setFillColor( dqOverworldRenderer->cheatText, dqRenderConfig->cheatFontColor );
}

void dqOverworldRenderer_Cleanup()
{
   int i;

   dqText_Destroy( dqOverworldRenderer->cheatText );
   dqFont_Destroy( dqOverworldRenderer->cheatFont );

   dqRectangleShape_Destroy( dqOverworldRenderer->passableRect );
   dqRectangleShape_Destroy( dqOverworldRenderer->impassableRect );
   dqRectangleShape_Destroy( dqOverworldRenderer->mapSwapRect );

   for ( i = 0; i < 4; i++ )
   {
      dqRectangleShape_Destroy( dqOverworldRenderer->occlusions[i] );
   }

   dqSprite_Destroy( dqOverworldRenderer->tileSprite );

   dqFree( dqOverworldRenderer, sizeof( dqOverworldRenderer_t ), sfTrue );
}

// TODO: I think a LOT of this can be consolidated

void dqOverworldRenderer_RenderMap()
{
   static sfVector2f viewOffset, padding, tileOffset, tilePosition, paddingCache, tileOffsetCache;
   unsigned int startTileColumn, startTileRow, endTileColumn, endTileRow, columnCount, rowCount,
      startTileColumnCache, startTileRowCache, endTileColumnCache, endTileRowCache, i;
   dqMap_t* map = dqGameData_GetCurrentMap();

   // X calculations

   if ( map->size.x < dqRenderConfig->overworldViewSize.x )
   {
      viewOffset.x = 0;
      padding.x = ( dqRenderConfig->overworldViewSize.x / 2 ) - ( map->size.x / 2 );
      tileOffset.x = 0;
      startTileColumn = 0;
      endTileColumn = map->columns - 1;
      columnCount = endTileColumn;
   }
   else
   {
      viewOffset.x = dqGameData->player->overworldState->centerPosition.x - ( dqRenderConfig->overworldViewSize.x / 2 );
      padding.x = 0;

      if ( map->wrap )
      {
         if ( viewOffset.x < 0 )
         {
            padding.x = -viewOffset.x;
            viewOffset.x = 0;
            startTileColumn = 0;
            endTileColumn = (unsigned int)( ( dqRenderConfig->overworldViewSize.x - padding.x ) / dqGameConfig->mapTileSize );
         }
         else if ( ( viewOffset.x + dqRenderConfig->overworldViewSize.x ) >= map->size.x )
         {
            startTileColumn = (unsigned int)( viewOffset.x / dqGameConfig->mapTileSize );
            endTileColumn = map->columns - 1;
         }
         else
         {
            startTileColumn = (unsigned int)( viewOffset.x / dqGameConfig->mapTileSize );
            endTileColumn = (unsigned int)( ( viewOffset.x + dqRenderConfig->overworldViewSize.x ) / dqGameConfig->mapTileSize );
         }
      }
      else
      {
         if ( viewOffset.x < 0 )
         {
            viewOffset.x = 0;
         }
         else if ( ( viewOffset.x + dqRenderConfig->overworldViewSize.x ) >= map->size.x )
         {
            viewOffset.x = map->size.x - dqRenderConfig->overworldViewSize.x;
         }

         startTileColumn = (unsigned int)( viewOffset.x / dqGameConfig->mapTileSize );
         endTileColumn = (unsigned int)( ( viewOffset.x + dqRenderConfig->overworldViewSize.x ) / dqGameConfig->mapTileSize );
      }

      columnCount = endTileColumn - startTileColumn;
      tileOffset.x = viewOffset.x - ( startTileColumn * dqGameConfig->mapTileSize );
   }

   // Y calculations

   if ( map->size.y < dqRenderConfig->overworldViewSize.y )
   {
      viewOffset.y = 0;
      padding.y = ( dqRenderConfig->overworldViewSize.y / 2 ) - ( map->size.y / 2 );
      tileOffset.y = 0;
      startTileRow = 0;
      endTileRow = map->rows - 1;
      rowCount = endTileRow;
   }
   else
   {
      viewOffset.y = dqGameData->player->overworldState->centerPosition.y - ( dqRenderConfig->overworldViewSize.y / 2 );
      padding.y = 0;

      if ( map->wrap )
      {
         if ( viewOffset.y < 0 )
         {
            padding.y = -viewOffset.y;
            viewOffset.y = 0;
            startTileRow = 0;
            endTileRow = (unsigned int)( ( dqRenderConfig->overworldViewSize.y - padding.y ) / dqGameConfig->mapTileSize );
         }
         else if ( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) >= map->size.y )
         {
            startTileRow = (unsigned int)( viewOffset.y / dqGameConfig->mapTileSize );
            endTileRow = map->rows - 1;
         }
         else
         {
            startTileRow = (unsigned int)( viewOffset.y / dqGameConfig->mapTileSize );
            endTileRow = (unsigned int)( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) / dqGameConfig->mapTileSize );
         }

         rowCount = endTileRow - startTileRow;
      }
      else
      {
         if ( viewOffset.y < 0 )
         {
            viewOffset.y = 0;
         }
         else if ( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) >= map->size.y )
         {
            viewOffset.y = map->size.y - dqRenderConfig->overworldViewSize.y;
         }

         startTileRow = (unsigned int)( viewOffset.y / dqGameConfig->mapTileSize );
         endTileRow = (unsigned int)( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) / dqGameConfig->mapTileSize );
         rowCount = endTileRow - startTileRow;
      }

      tileOffset.y = viewOffset.y - ( startTileRow * dqGameConfig->mapTileSize );
   }

   // render map tiles

   dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

   if ( map->wrap )
   {
      if ( padding.x > 0 )
      {
         // wrap on the left
         startTileColumnCache = startTileColumn;
         startTileColumn = map->columns - (unsigned int)( padding.x / dqGameConfig->mapTileSize ) - 1;
         endTileColumnCache = endTileColumn;
         endTileColumn = map->columns - 1;
         tileOffsetCache.x = tileOffset.x;
         tileOffset.x = dqGameConfig->mapTileSize - ( padding.x - ( ( endTileColumn - startTileColumn ) * dqGameConfig->mapTileSize ) );
         paddingCache.x = padding.x;
         padding.x = 0;

         dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

         if ( padding.y > 0 )
         {
            // wrap the top-left corner
            startTileRowCache = startTileRow;
            startTileRow = map->rows - (unsigned int)( padding.y / dqGameConfig->mapTileSize ) - 1;
            endTileRowCache = endTileRow;
            endTileRow = map->rows - 1;
            tileOffsetCache.y = tileOffset.y;
            tileOffset.y = dqGameConfig->mapTileSize - ( padding.y - ( ( endTileRow - startTileRow ) * dqGameConfig->mapTileSize ) );
            paddingCache.y = padding.y;
            padding.y = 0;

            dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

            startTileRow = startTileRowCache;
            endTileRow = endTileRowCache;
            tileOffset.y = tileOffsetCache.y;
            padding.y = paddingCache.y;
         }
         else if ( endTileRow < (unsigned int)( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) / dqGameConfig->mapTileSize ) )
         {
            // wrap the bottom-left corner
            startTileRowCache = startTileRow;
            startTileRow = 0;
            endTileRowCache = endTileRow;
            endTileRow = (unsigned int)( dqRenderConfig->overworldViewSize.y / dqGameConfig->mapTileSize ) - rowCount;
            paddingCache.y = padding.y;
            padding.y = dqRenderConfig->overworldViewSize.y - ( ( endTileRow - 1 ) * dqGameConfig->mapTileSize );

            dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

            startTileRow = startTileRowCache;
            endTileRow = endTileRowCache;
            padding.y = paddingCache.y;
         }

         startTileColumn = startTileColumnCache;
         endTileColumn = endTileColumnCache;
         tileOffset.x = tileOffsetCache.x;
         padding.x = paddingCache.x;
      }
      else if ( endTileColumn < (unsigned int)( ( viewOffset.x + dqRenderConfig->overworldViewSize.x ) / dqGameConfig->mapTileSize ) )
      {
         // wrap on the right
         startTileColumnCache = startTileColumn;
         startTileColumn = 0;
         endTileColumnCache = endTileColumn;
         endTileColumn = (unsigned int)( dqRenderConfig->overworldViewSize.x / dqGameConfig->mapTileSize ) - columnCount;
         paddingCache.x = padding.x;
         padding.x = dqRenderConfig->overworldViewSize.x - ( ( endTileColumn - 1 ) * dqGameConfig->mapTileSize );

         dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

         if ( padding.y > 0 )
         {
            // wrap the top-right corner
            startTileRowCache = startTileRow;
            startTileRow = map->rows - (unsigned int)( padding.y / dqGameConfig->mapTileSize ) - 1;
            endTileRowCache = endTileRow;
            endTileRow = map->rows - 1;
            tileOffsetCache.y = tileOffset.y;
            tileOffset.y = dqGameConfig->mapTileSize - ( padding.y - ( ( endTileRow - startTileRow ) * dqGameConfig->mapTileSize ) );
            paddingCache.y = padding.y;
            padding.y = 0;

            dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

            startTileRow = startTileRowCache;
            endTileRow = endTileRowCache;
            tileOffset.y = tileOffsetCache.y;
            padding.y = paddingCache.y;
         }
         else if ( endTileRow < (unsigned int)( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) / dqGameConfig->mapTileSize ) )
         {
            // wrap the bottom-right corner
            startTileRowCache = startTileRow;
            startTileRow = 0;
            endTileRowCache = endTileRow;
            endTileRow = (unsigned int)( dqRenderConfig->overworldViewSize.y / dqGameConfig->mapTileSize ) - rowCount;
            paddingCache.y = padding.y;
            padding.y = dqRenderConfig->overworldViewSize.y - ( ( endTileRow - 1 ) * dqGameConfig->mapTileSize );

            dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

            startTileRow = startTileRowCache;
            endTileRow = endTileRowCache;
            padding.y = paddingCache.y;
         }

         startTileColumn = startTileColumnCache;
         endTileColumn = endTileColumnCache;
         padding.x = paddingCache.x;
      }

      if ( padding.y > 0 )
      {
         // wrap on the top
         startTileRowCache = startTileRow;
         startTileRow = map->rows - (unsigned int)( padding.y / dqGameConfig->mapTileSize ) - 1;
         endTileRowCache = endTileRow;
         endTileRow = map->rows - 1;
         tileOffsetCache.y = tileOffset.y;
         tileOffset.y = dqGameConfig->mapTileSize - ( padding.y - ( ( endTileRow - startTileRow ) * dqGameConfig->mapTileSize ) );
         paddingCache.y = padding.y;
         padding.y = 0;

         dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

         startTileRow = startTileRowCache;
         endTileRow = endTileRowCache;
         tileOffset.y = tileOffsetCache.y;
         padding.y = paddingCache.y;
      }
      else if ( endTileRow < (unsigned int)( ( viewOffset.y + dqRenderConfig->overworldViewSize.y ) / dqGameConfig->mapTileSize ) )
      {
         // wrap on the bottom
         startTileRowCache = startTileRow;
         startTileRow = 0;
         endTileRowCache = endTileRow;
         endTileRow = (unsigned int)( dqRenderConfig->overworldViewSize.y / dqGameConfig->mapTileSize ) - rowCount;
         paddingCache.y = padding.y;
         padding.y = dqRenderConfig->overworldViewSize.y - ( ( endTileRow - 1 ) * dqGameConfig->mapTileSize );

         dqOverworldRenderer_RenderMapSection( map, &tileOffset, &padding, startTileColumn, endTileColumn, startTileRow, endTileRow );

         startTileRow = startTileRowCache;
         endTileRow = endTileRowCache;
         padding.y = paddingCache.y;
      }
   }

   // render entities and border occlusions

   dqOverworldRenderer_RenderEntities( &viewOffset, &padding );

   for ( i = 0; i < 4; i++ )
   {
      dqWindow_DrawRectangleShape( dqOverworldRenderer->occlusions[i] );
   }
}

static void dqOverworldRenderer_RenderMapSection( dqMap_t* map, sfVector2f* tileOffset, sfVector2f* padding,
                                                  unsigned int startTileColumn, unsigned int endTileColumn,
                                                  unsigned int startTileRow, unsigned int endTileRow )
{
   unsigned int i, j, row, column;
   static sfVector2f tilePosition;
   dqMapTile_t* tile;

   for ( i = 0, row = startTileRow; row <= endTileRow; row++, i++ )
   {
      for ( j = 0, column = startTileColumn; column <= endTileColumn; column++, j++ )
      {
         tile = dqMap_GetTileFromCoordinates( map, column, row );

         dqOverworldRenderer->tileTextureRect.left = (int)( ( tile->tileId % 16 ) * dqGameConfig->mapTileSize );
         dqOverworldRenderer->tileTextureRect.top = (int)( ( tile->tileId / 16 ) * dqGameConfig->mapTileSize );

         sfSprite_setTextureRect( dqOverworldRenderer->tileSprite, dqOverworldRenderer->tileTextureRect );

         tilePosition.x = ( j * dqGameConfig->mapTileSize ) - tileOffset->x + padding->x + dqRenderConfig->overworldViewOffset.x;
         tilePosition.y = ( i * dqGameConfig->mapTileSize ) - tileOffset->y + padding->y + dqRenderConfig->overworldViewOffset.y;

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
}

static void dqOverworldRenderer_RenderEntities( sfVector2f* viewOffset, sfVector2f* padding )
{
   static sfVector2f screenPosition;
   dqEntitySprite_t* playerSprite = dqGameData->player->entitySprite;

   screenPosition.x = playerSprite->entityOverworldState->hitBoxPosition.x
      - playerSprite->hitBoxOffset.x
      - viewOffset->x
      + padding->x
      + dqRenderConfig->overworldViewOffset.x;
   screenPosition.y = playerSprite->entityOverworldState->hitBoxPosition.y
      - playerSprite->hitBoxOffset.y
      - viewOffset->y
      + padding->y
      + dqRenderConfig->overworldViewOffset.y;

   sfSprite_setPosition( playerSprite->sprite, screenPosition );
   dqWindow_DrawEntitySprite( playerSprite );
}
