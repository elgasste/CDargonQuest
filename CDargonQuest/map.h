#pragma once

#include "common.h"

typedef struct dqMapTile_t dqMapTile_t;

typedef struct dqMap_t
{
   dqMapTile_t* tiles;
   unsigned int tileCount;
   unsigned int columns;
   unsigned int rows;
   sfVector2f size;
}
dqMap_t;

dqMapTile_t* dqMap_GetTile( dqMap_t* map, unsigned int column, unsigned int row );
