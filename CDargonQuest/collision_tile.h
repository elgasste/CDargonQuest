#pragma once

#include "common.h"

typedef struct
{
   sfBool isPassable;
   sfBool slowsMovement;
   sfBool isWater;
   unsigned int damage;
}
dqCollisionTile_t;
