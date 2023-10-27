#pragma once

#include "common.h"

typedef struct dqCollisionTile_t
{
   sfBool isPassable;
   sfBool slowsMovement;
   sfBool isWater;
   unsigned int damage;
}
dqCollisionTile_t;
