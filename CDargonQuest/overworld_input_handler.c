#include "overworld_input_handler.h"
#include "input_state.h"
#include "event_queue.h"
#include "direction.h"

void dqOverworldInputHandler_HandleInput()
{
   sfBool leftIsDown, upIsDown, rightIsDown, downIsDown;

   if ( dqInputState_WasKeyPressed( sfKeyEscape ) )
   {
      dqEventQueue_Push( dqEventQuit, 0 );
      return;
   }

   leftIsDown = dqInputState_IsKeyDown( sfKeyLeft );
   upIsDown = dqInputState_IsKeyDown( sfKeyUp );
   rightIsDown = dqInputState_IsKeyDown( sfKeyRight );
   downIsDown = dqInputState_IsKeyDown( sfKeyDown );

   if ( leftIsDown && !rightIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 1, (int)dqDirectionLeft );
   }
   else if ( rightIsDown && !leftIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 1, (int)dqDirectionRight );
   }

   if ( upIsDown && !downIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 1, (int)dqDirectionUp );
   }
   else if ( downIsDown && !upIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 1, (int)dqDirectionDown );
   }
}
