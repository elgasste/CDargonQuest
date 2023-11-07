#pragma once

#include "common.h"

typedef struct dqMapTile_t
{
   unsigned int tileId;

   sfBool isPassable;

   sfBool isExit;
   unsigned int exitMapIndex;
   unsigned int entranceTileIndex;
}
dqMapTile_t;
