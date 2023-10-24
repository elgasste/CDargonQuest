#pragma once

#include "common.h"

typedef struct dqGameConfig_t
{
   float maxPlayerVelocity;
}
dqGameConfig_t;

dqGameConfig_t* dqGameConfig;

void dqGameConfig_Init();
void dqGameConfig_Cleanup();
