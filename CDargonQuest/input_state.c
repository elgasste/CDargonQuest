#include "input_state.h"

void dqInputState_Init()
{
   dqInputState = (dqInputState_t*)dqMalloc( sizeof( dqInputState_t ) );

   dqInputState->keysPressed = (sfBool*)dqCalloc( sizeof( sfBool ), sfKeyCount );
   dqInputState->keysReleased = (sfBool*)dqCalloc( sizeof( sfBool ), sfKeyCount );
   dqInputState->keyWasPressed = sfFalse;
   dqInputState->lastPressedKey = sfKeyCount;
}

void dqInputState_Cleanup()
{
   dqFree( dqInputState->keysPressed );
   dqFree( dqInputState->keysReleased );
   dqFree( dqInputState );
}

void dqInputState_Reset()
{
   int i;

   for ( i = 0; i < (int)sfKeyCount; i++ )
   {
      dqInputState->keysPressed[i] = sfFalse;
      dqInputState->keysReleased[i] = sfFalse;
      dqInputState->keyWasPressed = sfFalse;
   }
}

void dqInputState_SetKeyPressed( sfKeyCode keyCode )
{
   if ( keyCode >= 0 && keyCode < sfKeyCount )
   {
      dqInputState->keysPressed[keyCode] = sfTrue;
      dqInputState->keyWasPressed = sfTrue;
      dqInputState->lastPressedKey = keyCode;
   }
}

void dqInputState_SetKeyReleased( sfKeyCode keyCode )
{
   if ( keyCode >= 0 && keyCode < sfKeyCount )
   {
      dqInputState->keysReleased[keyCode] = sfTrue;
   }
}

sfBool dqInputState_WasKeyPressed( sfKeyCode keyCode )
{
   return ( keyCode >= 0 && keyCode < sfKeyCount ) ? dqInputState->keysPressed[keyCode] : sfFalse;
}

sfBool dqInputState_WasKeyReleased( sfKeyCode keyCode )
{
   return ( keyCode >= 0 && keyCode < sfKeyCount) ? dqInputState->keysReleased[keyCode] : sfFalse;
}

sfBool dqInputState_IsKeyDown( sfKeyCode keyCode )
{
   return keyCode >= 0 ? sfKeyboard_isKeyPressed( keyCode ) : sfFalse;
}

sfBool dqInputState_IsAnyKeyDown()
{
   int i;

   for ( i = 0; i < (int)sfKeyCount; i++ )
   {
      if ( sfKeyboard_isKeyPressed( i ) )
      {
         return sfTrue;
      }
   }
   
   return sfFalse;
}
