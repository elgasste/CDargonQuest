#include "input_state.h"

void dqInputState_Init()
{
   dqInputState_Create();

   // TODO: create pressed and released maps
}

void dqInputState_Create()
{
   // TODO: allocate memory
}

void dqInputState_Cleanup()
{
   SAFE_DELETE( dqInputState->keysPressed )
   SAFE_DELETE( dqInputState->keysReleased )
   SAFE_DELETE( dqInputState )
}
