#pragma once

#include "common.h"

typedef struct dqCollisionTile_t dqCollisionTile_t;

typedef struct
{
   dqCollisionTile_t* tiles;
   unsigned int tileCount;
   unsigned int columns;
   unsigned int rows;
   float width;
   float height;
}
dqCollisionMap_t;
