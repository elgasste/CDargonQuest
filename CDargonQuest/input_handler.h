#pragma once

#include "common.h"

typedef struct dqInputHandler_t
{
   char cheatString[32];
}
dqInputHandler_t;

dqInputHandler_t* dqInputHandler;

void dqInputHandler_Init();
void dqInputHandler_Cleanup();
void dqInputHandler_HandleInput();
