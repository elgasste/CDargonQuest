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
   float encounterRate;
}
dqMapTile_t;
