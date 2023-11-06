#include "event_queue.h"

void dqEventQueue_Init()
{
   dqEventQueue = (dqEventQueue_t*)malloc( sizeof( dqEventQueue_t ) );
   dqEventQueue_Flush();
}

void dqEventQueue_Cleanup()
{
   SAFE_DELETE( dqEventQueue );
}

sfBool dqEventQueue_IsEmpty()
{
   return dqEventQueue->back == -1;
}

void dqEventQueue_Push( dqEventType_t type, int argCount, ... )
{
   int i;
   va_list args;

   dqEventQueue->back++;

   if ( dqEventQueue->back >= MAX_EVENTS )
   {
      dqError_ExitWithMessage( STR_ERROR_EVENT_OVERFLOW );
   }
   else
   {
      dqEventQueue->queue[dqEventQueue->back].type = type;

      if ( argCount > 0 )
      {
         va_start( args, argCount );

         for ( i = 0; i < argCount; i++ )
         {
            dqEventQueue->queue[dqEventQueue->back].args.argList[i] = va_arg( args, int );
         }

         va_end( args );
      }
   }
}

dqEvent_t* dqEventQueue_GetNext()
{
   dqEvent_t* e = &( dqEventQueue->queue[dqEventQueue->front] );
   dqEventQueue->front++;

   if ( dqEventQueue->front > dqEventQueue->back )
   {
      dqEventQueue_Flush();
   }

   return e;
}

void dqEventQueue_Flush()
{
   dqEventQueue->front = 0;
   dqEventQueue->back = -1;
}
