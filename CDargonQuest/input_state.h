#pragma once

#include "common.h"

typedef struct
{
   sfBool* keysPressed;
   sfBool* keysReleased;
}
dqInputState_t;

dqInputState_t* dqInputState;

void dqInputState_Init();
void dqInputState_Create();
void dqInputState_Cleanup();
