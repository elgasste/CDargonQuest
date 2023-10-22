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
void dqInputState_Cleanup();
void dqInputState_SetKeyPressed( sfKeyCode keyCode );
void dqInputState_SetKeyReleased( sfKeyCode keyCode );
void dqInputState_Reset();

sfBool dqInputState_WasKeyPressed( sfKeyCode keyCode );
sfBool dqInputState_WasKeyReleased( sfKeyCode keyCode );
sfBool dqInputState_IsAnyKeyDown();
