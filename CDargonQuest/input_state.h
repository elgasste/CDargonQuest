#if !defined( DQ_INPUT_STATE_H )
#define DQ_INPUT_STATE_H

#include "common.h"

typedef struct dqInputState_t
{
   sfBool* keysPressed;
   sfBool* keysReleased;
   sfBool keyWasPressed;
   sfKeyCode lastPressedKey;
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
sfBool dqInputState_IsKeyDown( sfKeyCode keyCode );
sfBool dqInputState_IsAnyKeyDown();

#endif
