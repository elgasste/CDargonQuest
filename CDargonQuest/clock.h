#if !defined( DQ_CLOCK_H )
#define DQ_CLOCK_H

#include "common.h"

typedef struct dqClock_t
{
   sfClock* clock;

   sfInt64 minFrameMicro;
   sfInt64 maxFrameMicro;

   sfTime frameStartTime;

   float minFrameSeconds;
   float maxFrameSeconds;
   float lastFrameSeconds;
   float totalSeconds;

   unsigned int frameCount;
   unsigned int lagFrameCount;

   unsigned int currentFrameRate;
   unsigned int averageFrameRate;
}
dqClock_t;

dqClock_t* dqClock;

void dqClock_Init();
void dqClock_Cleanup();
void dqClock_StartFrame();
void dqClock_EndFrame();

#endif
