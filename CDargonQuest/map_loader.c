#include <assert.h>

#include "map_loader.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"
#include "render_config.h"
#include "game_config.h"

void dqMapLoader_LoadTempMap( dqMap_t* map );
unsigned int dqMapLoader_TileIdFromInt( int i );
sfBool dqMapLoader_BoolFromInt( int i );

void dqMapLoader_LoadMaps()
{
   // TODO: temporary maps for now, these will be loaded from a file later
   dqGameData->mapCount = 2;
   dqGameData->maps = (dqMap_t*)malloc( sizeof( dqMap_t ) * dqGameData->mapCount );
   CHECK_MALLOC( dqGameData->maps )

   dqMapLoader_LoadTempMap( &( dqGameData->maps[0] ) );
   dqMapLoader_LoadTempMap( &( dqGameData->maps[1] ) );
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

void dqMapLoader_LoadTempMap( dqMap_t* map )
{
   errno_t err;
   FILE* tileFile;
   FILE* passableFile;
   unsigned int i;
   int fileIndex, newLine;

   map->columns = 51;
   map->rows = 43;
   map->size.x = map->columns * dqGameConfig->mapTileSize;
   map->size.y = map->rows * dqGameConfig->mapTileSize;
   map->tileCount = map->columns * map->rows;
   map->tiles = (dqMapTile_t*)malloc( sizeof( dqMapTile_t ) * map->tileCount );
   CHECK_MALLOC( map->tiles )

   err = fopen_s( &tileFile, "Resources\\Design\\Maps\\tiles.txt", "r" );

   if ( err )
   {
      dqError_ExitWithMessage( "could not open map tiles file" );
   }

   err = fopen_s( &passableFile, "Resources\\Design\\Maps\\passable.txt", "r" );

   if ( err )
   {
      dqError_ExitWithMessage( "could not open map passable file" );
   }

   if ( tileFile && passableFile )
   {
      for ( i = 0, fileIndex = 0; i < ( map->columns * map->rows ); i++, fileIndex++ )
      {
         map->tiles[i].textureId = 0;
         map->tiles[i].tileId = dqMapLoader_TileIdFromInt( fgetc( tileFile ) );
         map->tiles[i].isPassable = dqMapLoader_BoolFromInt( fgetc( passableFile ) );

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

unsigned int dqMapLoader_TileIdFromInt( int i )
{
   // numbers start at 48 and lower-case characters start at 97
   return ( i >= 48 && i <= 57 ) ? i - 48 : i - 87;
}

sfBool dqMapLoader_BoolFromInt( int i )
{
   // 48 is zero
   return i == 48 ? sfFalse : sfTrue;
}
