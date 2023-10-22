#pragma once

#include "common.h"

typedef struct
{
   unsigned long long minFrameDuration;
   unsigned long long maxFrameDuration;
   unsigned long long frameStart;

   float minFrameSeconds;
   float maxFrameSeconds;
   float lastFrameSeconds;
   float totalSeconds;

   unsigned int frameCount;
   unsigned int lagFrameCount;

   unsigned int minTimePeriod;
}
dqClock_t;

dqClock_t* dqClock;

void dqClock_Init();
void dqClock_Cleanup();
void dqClock_StartFrame();
void dqClock_EndFrame();
unsigned int dqClock_CurrentFrameRate();
unsigned int dqClock_AverageFrameRate();
