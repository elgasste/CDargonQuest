#pragma once

#include "common.h"
#include "map.h"
#include "entity.h"

typedef struct dqGameData_t
{
   dqMap_t* maps;
   unsigned int mapCount;

   dqEntity_t* player;
}
dqGameData_t;

dqGameData_t* dqGameData;

void dqGameData_Init();
void dqGameData_Cleanup();
