#include "overworld_input_handler.h"
#include "input_state.h"
#include "event_queue.h"
#include "direction.h"

void dqOverworldInputHandler_Init()
{
   dqOverworldInputHandler = (dqOverworldInputHandler_t*)malloc( sizeof( dqOverworldInputHandler_t ) );
   CHECK_MALLOC( dqOverworldInputHandler )

   dqOverworldInputHandler->useDirectionCache = sfFalse;
}

void dqOverworldInputHandler_Cleanup()
{
   SAFE_DELETE( dqOverworldInputHandler );
}

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

   if ( !leftIsDown && !upIsDown && !rightIsDown && !downIsDown )
   {
      dqOverworldInputHandler->useDirectionCache = sfFalse;
      return;
   }

   if ( leftIsDown && !rightIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 2, (int)dqDirectionLeft, (int)( ( upIsDown && !downIsDown ) || ( downIsDown && !upIsDown ) ) );
      dqOverworldInputHandler_PointPlayer( dqDirectionLeft,
                                           dqDirectionUp, upIsDown && !downIsDown,
                                           dqDirectionDown, downIsDown && !upIsDown );
   }
   else if ( rightIsDown && !leftIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 2, (int)dqDirectionRight, (int)( ( upIsDown && !downIsDown ) || ( downIsDown && !upIsDown ) ) );
      dqOverworldInputHandler_PointPlayer( dqDirectionRight,
                                           dqDirectionUp, upIsDown && !downIsDown,
                                           dqDirectionDown, downIsDown && !upIsDown );
   }

   if ( upIsDown && !downIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 2, (int)dqDirectionUp, (int)( ( leftIsDown && !rightIsDown ) || ( rightIsDown && !leftIsDown ) ) );
      dqOverworldInputHandler_PointPlayer( dqDirectionUp,
                                           dqDirectionLeft, leftIsDown && !rightIsDown,
                                           dqDirectionRight, rightIsDown && !leftIsDown );
   }
   else if ( downIsDown && !upIsDown )
   {
      dqEventQueue_Push( dqEventMovePlayer, 2, (int)dqDirectionDown, (int)( ( leftIsDown && !rightIsDown ) || ( rightIsDown && !leftIsDown ) ) );
      dqOverworldInputHandler_PointPlayer( dqDirectionDown,
                                           dqDirectionLeft, leftIsDown && !rightIsDown,
                                           dqDirectionRight, rightIsDown && !leftIsDown );
   }
}

void dqOverworldInputHandler_PointPlayer( dqDirection direction,
                                          dqDirection allowedCache1, sfBool cacheCheck1,
                                          dqDirection allowedCache2, sfBool cacheCheck2 )
{
   sfBool canUseCache = ( ( dqOverworldInputHandler->directionCache == allowedCache1 ) && cacheCheck1 ) ||
                        ( ( dqOverworldInputHandler->directionCache == allowedCache2 ) && cacheCheck2 );

   if ( dqOverworldInputHandler->useDirectionCache && canUseCache )
   {
      dqEventQueue_Push( dqEventPointPlayer, 1, (int)dqOverworldInputHandler->directionCache );
   }
   else
   {
      dqOverworldInputHandler->useDirectionCache = sfTrue;
      dqOverworldInputHandler->directionCache = direction;
      dqEventQueue_Push( dqEventPointPlayer, 1, (int)direction );
   }
}
