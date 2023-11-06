#pragma once

#include "common.h"

typedef struct dqTransitionRenderer_t
{
   float fadeInSeconds;
   float fadeOutSeconds;
   float elapsedSeconds;
}
dqTransitionRenderer_t;

dqTransitionRenderer_t* dqTransitionRenderer;

void dqTransitionRenderer_Init();
void dqTransitionRenderer_Cleanup();
void dqTransitionRenderer_Reset();
void dqTransitionRenderer_Render();
