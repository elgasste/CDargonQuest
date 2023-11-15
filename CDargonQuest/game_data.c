#include "game_config.h"
#include "game_data.h"
#include "map_loader.h"
#include "player.h"
#include "map.h"
#include "enemy_template.h"

static void dqGameData_TempLoadEnemyTemplates();

void dqGameData_Init()
{
   dqGameData = (dqGameData_t*)dqMalloc( sizeof( dqGameData_t ), sfTrue );

   dqMapLoader_LoadMaps();

   // TODO: this should come from a data file eventually
   dqGameData->playerStartTileCoordinates.x = 28;
   dqGameData->playerStartTileCoordinates.y = 35;
   dqGameData->player = dqPlayer_Create();

   dqGameData_TempLoadEnemyTemplates();
}

void dqGameData_Cleanup()
{
   unsigned int i;

   dqPlayer_Cleanup( dqGameData->player );
   dqMapLoader_CleanupMaps();

   for ( i = 0; i < dqGameData->enemyTierCount; i++ )
   {
      dqFree( dqGameData->enemyTemplates[i], sizeof( dqEnemyTemplate_t ) * (size_t)( dqGameData->enemyTemplateCount ), sfTrue);
   }

   dqFree( dqGameData->enemyTemplates, sizeof( dqEnemyTemplate_t* ) * (size_t)( dqGameData->enemyTierCount ), sfTrue );
   dqFree( dqGameData, sizeof( dqGameData_t ), sfTrue );
}

dqMap_t* dqGameData_GetCurrentMap()
{
   return &( dqGameData->maps[dqGameData->currentMapIndex] );
}

static void dqGameData_TempLoadEnemyTemplates()
{
   unsigned int i;

   dqGameData->enemyTierCount = 2;
   dqGameData->enemyTemplateCount = 2;
   dqGameData->enemyTemplates = (dqEnemyTemplate_t**)dqMalloc( sizeof( dqEnemyTemplate_t* ) *
                                                               (size_t)( dqGameData->enemyTierCount ),
                                                               sfTrue );

   for ( i = 0; i < dqGameData->enemyTierCount; i++ )
   {
      dqGameData->enemyTemplates[i] = (dqEnemyTemplate_t*)dqMalloc( sizeof( dqEnemyTemplate_t ) *
                                                                    (size_t)( dqGameData->enemyTemplateCount ),
                                                                    sfTrue );
   }

   // TODO: don't worry about the graphics for now, just generate some data to test with
   sprintf_s( dqGameData->enemyTemplates[0][0].name, ENTITY_NAME_SIZE, "slime" );
   dqGameData->enemyTemplates[0][0].minHitPoints = 4;
   dqGameData->enemyTemplates[0][0].maxHitPoints = 6;
   dqGameData->enemyTemplates[0][0].attackPower = 2;
   dqGameData->enemyTemplates[0][0].defensePower = 2;

   sprintf_s( dqGameData->enemyTemplates[0][1].name, ENTITY_NAME_SIZE, "black raven" );
   dqGameData->enemyTemplates[0][1].minHitPoints = 6;
   dqGameData->enemyTemplates[0][1].maxHitPoints = 9;
   dqGameData->enemyTemplates[0][1].attackPower = 3;
   dqGameData->enemyTemplates[0][1].defensePower = 3;

   sprintf_s( dqGameData->enemyTemplates[1][0].name, ENTITY_NAME_SIZE, "horned rabbit" );
   dqGameData->enemyTemplates[1][0].minHitPoints = 8;
   dqGameData->enemyTemplates[1][0].maxHitPoints = 12;
   dqGameData->enemyTemplates[1][0].attackPower = 4;
   dqGameData->enemyTemplates[1][0].defensePower = 4;

   sprintf_s( dqGameData->enemyTemplates[1][1].name, ENTITY_NAME_SIZE, "giant anteater" );
   dqGameData->enemyTemplates[1][1].minHitPoints = 10;
   dqGameData->enemyTemplates[1][1].maxHitPoints = 14;
   dqGameData->enemyTemplates[1][1].attackPower = 7;
   dqGameData->enemyTemplates[1][1].defensePower = 3;
}
