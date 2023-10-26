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
void dqGame_HandleEvents();
void dqGame_Tick();
void dqGame_HandleStart();
void dqGame_HandleQuit();
void dqGame_HandleMovePlayer( dqEvent_t* e );
void dqGame_HandlePointPlayer( dqEvent_t* e );
