#if !defined( DQ_GAME_DATA_H )
#define DQ_GAME_DATA_H

#include "common.h"

typedef struct dqMap_t dqMap_t;
typedef struct dqPlayer_t dqPlayer_t;
typedef struct dqEnemyTemplate_t dqEnemyTemplate_t;

typedef struct dqGameData_t
{
   dqMap_t* maps;
   unsigned int mapCount;
   unsigned int currentMapIndex;

   dqPlayer_t* player;
   sfVector2u playerStartTileCoordinates;

   dqEnemyTemplate_t** enemyTemplates;
   unsigned int enemyTierCount;
   unsigned int enemyTemplateCount;
}
dqGameData_t;

dqGameData_t* dqGameData;

void dqGameData_Init();
void dqGameData_Cleanup();
dqMap_t* dqGameData_GetCurrentMap();

#endif
