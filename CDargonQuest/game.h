#pragma once

#include "common.h"
#include "state.h"
#include "menu.h"

typedef struct
{
   sfBool isRunning;
   dqState_t state;

   dqMenu_t* titleMenu;
}
dqGame_t;

dqGame_t* dqGame;

void dqGame_Init();
void dqGame_Create();
void dqGame_Cleanup();
void dqGame_Run();
void dqGame_HandleEvents();
void dqGame_Tick();
void dqGame_Quit();
