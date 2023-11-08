#pragma once

#include "common.h"
#include "direction.h"

typedef struct dqMapTile_t
{
   unsigned int tileId;
   sfBool isPassable;
   sfBool isExit;
   unsigned int exitMapIndex;
   unsigned int entranceTileIndex;
   sfBool hasEntranceDirection;
   dqDirection entranceDirection;
   unsigned int encounterRate;
   unsigned int minEnemyTier;
   unsigned int maxEnemyTier;
}
dqMapTile_t;
