#pragma once

#include "common.h"

typedef struct dqCollisionTile_t dqCollisionTile_t;

typedef struct dqCollisionMap_t
{
   dqCollisionTile_t* tiles;
   unsigned int tileCount;
   unsigned int columns;
   unsigned int rows;
   sfVector2f size;
}
dqCollisionMap_t;
