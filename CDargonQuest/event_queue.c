#include "event_queue.h"

void dqEventQueue_Init()
{
   dqEventQueue_Create();

   dqEventQueue->front = 0;
   dqEventQueue->back = -1;
}

void dqEventQueue_Create()
{
   dqEventQueue = (dqEventQueue_t*)malloc( sizeof( dqEventQueue_t ) );

   if ( !dqEventQueue )
   {
      dqError_ExitWithMessage( STR_ERROR_EVENT_QUEUE_MEMORY );
   }
}

void dqEventQueue_Cleanup()
{
   SAFE_DELETE( dqEventQueue );
}

sfBool dqEventQueue_IsEmpty()
{
   return dqEventQueue->back == -1;
}

void dqEventQueue_Push( dqGameEventType_t e )
{
   dqEventQueue->back++;

   if ( dqEventQueue->back >= MAX_GAME_EVENTS )
   {
      dqError_ExitWithMessage( STR_ERROR_EVENT_OVERFLOW );
   }
   else
   {
      dqEventQueue->queue[dqEventQueue->back] = e;
   }
}

dqGameEventType_t dqEventQueue_GetNext()
{
   dqGameEventType_t e = dqEventQueue->queue[dqEventQueue->front];
   dqEventQueue->front++;

   if ( dqEventQueue->front > dqEventQueue->back )
   {
      dqEventQueue->front = 0;
      dqEventQueue->back = -1;
   }

   return e;
}

dqGameEventType_t dqEventQueue_PeekNext()
{
   return dqEventQueue->queue[dqEventQueue->front];
}
