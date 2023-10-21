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
