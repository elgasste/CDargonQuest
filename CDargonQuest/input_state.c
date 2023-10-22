#include "input_state.h"

void dqInputState_Init()
{
   dqInputState_Create();

   dqInputState->keysPressed = (sfBool*)calloc( sizeof( sfBool ), sfKeyCount );
   dqInputState->keysReleased = (sfBool*)calloc( sizeof( sfBool ), sfKeyCount );
}

void dqInputState_Create()
{
   dqInputState = (dqInputState_t*)malloc( sizeof( dqInputState_t ) );

   if ( !dqInputState )
   {
      dqError_ExitWithMessage( STR_ERROR_INPUT_STATE_MEMORY );
   }
}

void dqInputState_Cleanup()
{
   SAFE_DELETE( dqInputState->keysPressed )
   SAFE_DELETE( dqInputState->keysReleased )
   SAFE_DELETE( dqInputState )
}

void dqInputState_Reset()
{
   static int i;

   for ( i = 0; i < (int)sfKeyCount; i++ )
   {
      dqInputState->keysPressed[i] = sfFalse;
      dqInputState->keysReleased[i] = sfFalse;
   }
}

void dqInputState_SetKeyPressed( sfKeyCode keyCode )
{
   dqInputState->keysPressed[(int)keyCode] = sfTrue;
}

void dqInputState_SetKeyReleased( sfKeyCode keyCode )
{
   dqInputState->keysReleased[(int)keyCode] = sfTrue;
}

sfBool dqInputState_WasKeyPressed( sfKeyCode keyCode )
{
   return dqInputState->keysPressed[keyCode];
}

sfBool dqInputState_WasKeyReleased( sfKeyCode keyCode )
{
   return dqInputState->keysReleased[keyCode];
}

sfBool dqInputState_IsAnyKeyDown()
{
   static int i;

   for ( i = 0; i < (int)sfKeyCount; i++ )
   {
      if ( sfKeyboard_isKeyPressed( i ) )
      {
         return sfTrue;
      }
   }
   
   return sfFalse;
}
