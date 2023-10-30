#pragma once

#include "common.h"
#include "direction.h"

typedef struct
{
   sfBool useDirectionCache;
   dqDirection directionCache;
}
dqOverworldInputHandler_t;

dqOverworldInputHandler_t* dqOverworldInputHandler;

void dqOverworldInputHandler_Init();
void dqOverworldInputHandler_Cleanup();
void dqOverworldInputHandler_HandleInput();
