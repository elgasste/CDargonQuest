#pragma once

#include "common.h"
#include "state.h"
#include "event.h"

typedef struct dqGame_t
{
   sfBool isRunning;
   dqState_t state;
}
dqGame_t;

dqGame_t* dqGame;

void dqGame_Init();
void dqGame_Cleanup();
void dqGame_Run();
