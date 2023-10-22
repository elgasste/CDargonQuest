#pragma once

#include "common.h"
#include "state.h"

typedef struct
{
   sfBool isRunning;
   dqGameState_t state;
}
dqGame_t;

dqGame_t* dqGame;

void dqGame_Init();
void dqGame_Create();
void dqGame_Cleanup();
void dqGame_Run();
void dqGame_Tick();
