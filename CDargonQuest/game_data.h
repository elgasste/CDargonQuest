#pragma once

#include "common.h"
#include "map.h"

typedef struct
{
   dqMap_t* maps;
   unsigned int mapCount;
}
dqGameData_t;

dqGameData_t* dqGameData;

void dqGameData_Init();
void dqGameData_Cleanup();
