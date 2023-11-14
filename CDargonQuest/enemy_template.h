#pragma once

#include "common.h"

typedef struct dqEnemyTemplate_t
{
   char* name[ENTITY_NAME_SIZE];

   unsigned int minHitPoints;
   unsigned int maxHitPoints;
}
dqEnemyTemplate_t;
