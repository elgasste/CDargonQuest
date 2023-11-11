#include <assert.h>

#include "map_loader.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"
#include "render_config.h"
#include "game_config.h"

static void dqMapLoader_LoadTempMap( dqMap_t* map, unsigned int columns, unsigned int rows,
                                     const char* tilesPath, const char* passablePath, const char* encounterPath,
                                     const char* minTiersPath, const char* maxTiersPath );
static unsigned int dqMapLoader_TileIdFromInt( int i );
static sfBool dqMapLoader_BoolFromInt( int i );
static unsigned int dqMapLoader_EncounterRateFromInt( int i );

void dqMapLoader_LoadMaps()
{
   dqMapTile_t* testExitTile;

   // TODO: temporary maps for now, these will be loaded from a file later
   dqGameData->mapCount = 2;
   dqGameData->maps = (dqMap_t*)dqMalloc( sizeof( dqMap_t ) * dqGameData->mapCount );

   dqMapLoader_LoadTempMap( &( dqGameData->maps[0] ), 51, 43,
                            "Resources\\Design\\Maps\\0_tiles.txt",
                            "Resources\\Design\\Maps\\0_passable.txt",
                            "Resources\\Design\\Maps\\0_encounter_rates.txt",
                            "Resources\\Design\\Maps\\0_min_enemy_tiers.txt",
                            "Resources\\Design\\Maps\\0_max_enemy_tiers.txt" );
   dqMapLoader_LoadTempMap( &( dqGameData->maps[1] ), 33, 40,
                            "Resources\\Design\\Maps\\1_tiles.txt",
                            "Resources\\Design\\Maps\\1_passable.txt",
                            "Resources\\Design\\Maps\\1_encounter_rates.txt",
                            "Resources\\Design\\Maps\\1_min_enemy_tiers.txt",
                            "Resources\\Design\\Maps\\1_max_enemy_tiers.txt");

   // overworld Aliahan entrance
   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 29, 32 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionRight;

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 30, 32 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionRight;

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 29, 33 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionRight;

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[0] ), 30, 33 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 1;
   testExitTile->entranceTileIndex = ( 24 * 33 ) + 1; // col 1, row 24
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionRight;

   // Aliahan west exit
   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 0, 24 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionDown;

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 0, 25 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionDown;

   // Aliahan south exit
   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 25, 39 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionDown;

   testExitTile = dqMap_GetTileFromCoordinates( &( dqGameData->maps[1] ), 26, 39 );
   testExitTile->isExit = sfTrue;
   testExitTile->exitMapIndex = 0;
   testExitTile->entranceTileIndex = ( 34 * 51 ) + 29; // col 29, row 33
   testExitTile->hasEntranceDirection = sfTrue;
   testExitTile->entranceDirection = dqDirectionDown;

   dqGameData->currentMapIndex = 0;
}

void dqMapLoader_CleanupMaps()
{
   unsigned int i;

   for ( i = 0; i < dqGameData->mapCount; i++ )
   {
      dqFree( dqGameData->maps[i].tiles );
   }

   dqFree( dqGameData->maps );
}

static void dqMapLoader_LoadTempMap( dqMap_t* map, unsigned int columns, unsigned int rows,
                                     const char* tilesPath, const char* passablePath, const char* encounterPath,
                                     const char* minTiersPath, const char* maxTiersPath )
{
   FILE* tileFile;
   FILE* passableFile;
   FILE* encounterFile;
   FILE* minTiersFile;
   FILE* maxTiersFile;
   unsigned int i;
   int fileIndex, newLine;

   map->columns = columns;
   map->rows = rows;
   map->size.x = map->columns * dqGameConfig->mapTileSize;
   map->size.y = map->rows * dqGameConfig->mapTileSize;
   map->tileCount = map->columns * map->rows;
   map->tiles = (dqMapTile_t*)dqMalloc( sizeof( dqMapTile_t ) * map->tileCount );

   if ( fopen_s( &tileFile, tilesPath, "r" ) )
   {
      dqError_ExitWithMessage( "could not open map tiles file" );
   }

   if ( fopen_s( &passableFile, passablePath, "r" ) )
   {
      dqError_ExitWithMessage( "could not open map passable file" );
   }

   if ( fopen_s( &encounterFile, encounterPath, "r" ) )
   {
      dqError_ExitWithMessage( "could not open map encounter file" );
   }

   if ( fopen_s( &minTiersFile, minTiersPath, "r" ) )
   {
      dqError_ExitWithMessage( "could not open map min tiers file" );
   }

   if ( fopen_s( &maxTiersFile, maxTiersPath, "r" ) )
   {
      dqError_ExitWithMessage( "could not open map max tiers file" );
   }

   if ( tileFile && passableFile && encounterFile && minTiersFile && maxTiersFile )
   {
      for ( i = 0, fileIndex = 0; i < map->tileCount; i++, fileIndex++ )
      {
         map->tiles[i].tileId = dqMapLoader_TileIdFromInt( fgetc( tileFile ) );
         map->tiles[i].isPassable = dqMapLoader_BoolFromInt( fgetc( passableFile ) );
         map->tiles[i].isExit = sfFalse;
         map->tiles[i].hasEntranceDirection = sfFalse;
         map->tiles[i].encounterRate = dqMapLoader_EncounterRateFromInt( fgetc( encounterFile ) );
         map->tiles[i].minEnemyTier = fgetc( minTiersFile ) - 48;
         map->tiles[i].maxEnemyTier = fgetc( maxTiersFile ) - 48;

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
            newLine = fgetc( encounterFile );
            assert( newLine == 10 );
            newLine = fgetc( minTiersFile );
            assert( newLine == 10 );
            newLine = fgetc( maxTiersFile );
            assert( newLine == 10 );
            fileIndex = -1;
         }
      }

      fclose( tileFile );
      fclose( passableFile );
      fclose( encounterFile );
      fclose( minTiersFile );
      fclose( maxTiersFile );
   }
}

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

static unsigned int dqMapLoader_EncounterRateFromInt( int i )
{
   // 48 is zero
   int adjustedValue = i - 48;

   switch ( adjustedValue )
   {
      case 1:
         return 5;
      case 2:
         return 10;
      case 3:
         return 15;
      default:
         return 0;
   }
}
