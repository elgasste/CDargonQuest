#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <timeapi.h>

#include "clock.h"
#include "render_config.h"

void dqClock_Init()
{
   TIMECAPS tc;
   MMRESULT res;

   dqClock = (dqClock_t*)malloc( sizeof( dqClock_t ) );

#pragma warning ( suppress:6011 )
   dqClock->minFrameSeconds = 1 / (float)dqRenderConfig->maxFrameRate;
   dqClock->maxFrameSeconds = 1 / (float)dqRenderConfig->minFrameRate;

   dqClock->minFrameDuration = (unsigned long long)( (double)dqClock->minFrameSeconds * 1000 );
   dqClock->maxFrameDuration = (unsigned long long)( (double)dqClock->maxFrameSeconds * 1000 );

   dqClock->frameCount = 0;
   dqClock->lagFrameCount = 0;
   dqClock->lastFrameSeconds = 0.0f;
   dqClock->totalSeconds = 0.0f;

   // set the timer resolution to the minimum possible value (more precision)
   timeGetDevCaps( &tc, sizeof( TIMECAPS ) );
   dqClock->minTimePeriod = tc.wPeriodMin;
   res = timeBeginPeriod( tc.wPeriodMin );

   if ( res != TIMERR_NOERROR )
   {
      dqError_ExitWithMessage( STR_ERROR_CLOCK_RESOLUTION );
   }
}

void dqClock_Cleanup()
{
   timeEndPeriod( dqClock->minTimePeriod );
   SAFE_DELETE( dqClock )
}

void dqClock_StartFrame()
{
   dqClock->frameStart = GetTickCount64();
}

void dqClock_EndFrame()
{
   static unsigned long long frameEnd, frameDuration;

   frameEnd = GetTickCount64();
   frameDuration = frameEnd - dqClock->frameStart;
   dqClock->frameCount++;

   if ( frameDuration > dqClock->maxFrameDuration )
   {
      dqClock->lastFrameSeconds = dqClock->maxFrameSeconds;
      dqClock->totalSeconds += dqClock->maxFrameSeconds;
      dqClock->lagFrameCount++;

      return;
   }
   else if ( frameDuration < dqClock->minFrameDuration )
   {
      // any "sleep" call is notoriously unreliable, so we'll try to do it, but we'll
      // still use the actual elapsed time below to record the last frame's seconds.
      Sleep( (DWORD)( dqClock->minFrameDuration - frameDuration ) );
   }

   dqClock->lastFrameSeconds = ( GetTickCount64() - dqClock->frameStart ) / 1000.0f;
   dqClock->totalSeconds += dqClock->lastFrameSeconds;
}
