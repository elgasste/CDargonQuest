#pragma once

#include "common.h"

#define CHEAT_STRING_SIZE 7

typedef struct dqInputHandler_t
{
   char cheatString[CHEAT_STRING_SIZE];
}
dqInputHandler_t;

dqInputHandler_t* dqInputHandler;

void dqInputHandler_Init();
void dqInputHandler_Cleanup();
void dqInputHandler_HandleInput();
