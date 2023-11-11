#include "clock.h"
#include "render_config.h"

void dqClock_Init()
{
   dqClock = (dqClock_t*)dqMalloc( sizeof( dqClock_t ) );

   dqClock->clock = sfClock_create();

   dqClock->minFrameSeconds = 1 / (float)dqRenderConfig->maxFrameRate;
   dqClock->maxFrameSeconds = 1 / (float)dqRenderConfig->minFrameRate;

   dqClock->minFrameMicro = (sfInt64)( (double)dqClock->minFrameSeconds * 1'000'000 );
   dqClock->maxFrameMicro = (sfInt64)( (double)dqClock->maxFrameSeconds * 1'000'000 );

   dqClock->frameCount = 0;
   dqClock->lagFrameCount = 0;
   dqClock->lastFrameSeconds = 0;
   dqClock->totalSeconds = 0;

   dqClock->currentFrameRate = 0;
   dqClock->averageFrameRate = 0;
}

void dqClock_Cleanup()
{
   sfClock_destroy( dqClock->clock );

   dqFree( dqClock );
}

void dqClock_StartFrame()
{
   dqClock->frameStartTime = sfClock_getElapsedTime( dqClock->clock );
}

void dqClock_EndFrame()
{
   sfTime frameEndTime = sfClock_getElapsedTime( dqClock->clock );
   static sfTime sleepTime = { 0 };
   sfInt64 frameDurationMicro = frameEndTime.microseconds - dqClock->frameStartTime.microseconds;

   dqClock->frameCount++;

   if ( frameDurationMicro > dqClock->maxFrameMicro )
   {
      dqClock->lastFrameSeconds = dqClock->maxFrameSeconds;
      dqClock->totalSeconds += dqClock->maxFrameSeconds;
      dqClock->lagFrameCount++;
   }
   else
   {
      if ( frameDurationMicro < dqClock->minFrameMicro )
      {
         sleepTime.microseconds = dqClock->minFrameMicro - frameDurationMicro;
         sfSleep( sleepTime );
      }

      frameEndTime = sfClock_getElapsedTime( dqClock->clock );
      dqClock->lastFrameSeconds = ( frameEndTime.microseconds - dqClock->frameStartTime.microseconds ) / 1'000'000.0f;
      dqClock->totalSeconds += dqClock->lastFrameSeconds;
   }

   dqClock->currentFrameRate = (unsigned int)( 1 / dqClock->lastFrameSeconds );
   dqClock->averageFrameRate = (unsigned int)( 1 / ( dqClock->totalSeconds / dqClock->frameCount ) );
}
