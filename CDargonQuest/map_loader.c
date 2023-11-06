#include <assert.h>

#include "map_loader.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"
#include "render_config.h"
#include "game_config.h"

static unsigned int dqMapLoader_TileIdFromInt( int i )
{
   // numbers start at 48 and lower-case characters start at 97
   if ( i >= 48 && i <= 57 )
   {
      // numbers start at 48
      return i - 48;
   }
   else if ( i >= 97 && i <= 122 )
   {
      // next are lower-case characters, which start at 97
      return i - ( 97 - 10 ); // account for numbers
   }
   else
   {
      // this must be upper-case characters, which start at 65
      return i - ( 65 - 36 ); // account for numbers and lower-case letters
   }
}

static sfBool dqMapLoader_BoolFromInt( int i )
{
   // 48 is zero
   return i == 48 ? sfFalse : sfTrue;
}

static void dqMapLoader_LoadTempMap( dqMap_t* map, unsigned int columns, unsigned int rows, const char* tilesPath, const char* passablePath )
{
   errno_t err;
   FILE* tileFile;
   FILE* passableFile;
   unsigned int i;
   int fileIndex, newLine;

   map->columns = columns;
   map->rows = rows;
   map->size.x = map->columns * dqGameConfig->mapTileSize;
   map->size.y = map->rows * dqGameConfig->mapTileSize;
   map->tileCount = map->columns * map->rows;
   map->tiles = (dqMapTile_t*)malloc( sizeof( dqMapTile_t ) * map->tileCount );
   CHECK_MALLOC( map->tiles )

      err = fopen_s( &tileFile, tilesPath, "r" );

   if ( err )
   {
      dqError_ExitWithMessage( "could not open map tiles file" );
   }

   err = fopen_s( &passableFile, passablePath, "r" );

   if ( err )
   {
      dqError_ExitWithMessage( "could not open map passable file" );
   }

   if ( tileFile && passableFile )
   {
      for ( i = 0, fileIndex = 0; i < map->tileCount; i++, fileIndex++ )
      {
         map->tiles[i].textureId = 0;
         map->tiles[i].tileId = dqMapLoader_TileIdFromInt( fgetc( tileFile ) );
         map->tiles[i].isPassable = dqMapLoader_BoolFromInt( fgetc( passableFile ) );
         map->tiles[i].isExit = sfFalse;

         if ( i == ( ( map->columns * map->rows ) - 1 ) )
         {
            break;
         }
         else if ( fileIndex == (int)( map->columns - 1 ) )
         {
            // 10 is a line feed
            newLine = fgetc( tileFile );
            assert( newLine == 10 );
            newLine = fgetc( passableFile );
            assert( newLine == 10 );
            fileIndex = -1;
         }
      }

      fclose( tileFile );
      fclose( passableFile );
   }
}

void dqMapLoader_LoadMaps()
{
   dqMapTile_t* testExitTile;

   // TODO: temporary maps for now, these will be loaded from a file later
   dqGameData->mapCount = 2;
   dqGameData->maps = (dqMap_t*)malloc( sizeof( dqMap_t ) * dqGameData->mapCount );
   CHECK_MALLOC( dqGameData->maps )

   dqMapLoader_LoadTempMap( &( dqGameData->maps[0] ), 51, 43, "Resources\\Design\\Maps\\0_tiles.txt", "Resources\\Design\\Maps\\0_passable.txt" );
   dqMapLoader_LoadTempMap( &( dqGameData->maps[1] ), 33, 40, "Resources\\Design\\Maps\\1_tiles.txt", "Resources\\Design\\Maps\\1_passable.txt" );

   // overworld Aliahan entrance
   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 29, 32 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 30, 32 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 29, 33 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 30, 33 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24

   // Aliahan west exit
   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 0, 24 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 0, 25 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33

   // Aliahan south exit
   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 25, 39 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 26, 39 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33

   dqGameData->currentMapIndex = 0;
}

void dqMapLoader_CleanupMaps()
{
   unsigned int i;

   for ( i = 0; i < dqGameData->mapCount; i++ )
   {
      SAFE_DELETE( dqGameData->maps[i].tiles );
   }

   SAFE_DELETE( dqGameData->maps );
}
