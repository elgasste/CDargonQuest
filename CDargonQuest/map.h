#pragma once

#include "common.h"
#include "map_tile.h"

typedef struct dqMap_t
{
   dqMapTile_t* tiles;
   unsigned int tileCount;
   unsigned int width;
   unsigned int height;
}
dqMap_t;

dqMapTile_t* dqMap_GetTile( dqMap_t* map, unsigned int x, unsigned int y );
