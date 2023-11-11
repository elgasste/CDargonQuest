#pragma once

#include "common.h"

typedef struct dqTitleRenderer_t
{
   sfBool showCarat;
   float caratElapsedSeconds;
   unsigned int selectedOptionCache;
}
dqTitleRenderer_t;

dqTitleRenderer_t* dqTitleRenderer;

void dqTitleRenderer_Init();
void dqTitleRenderer_Cleanup();
void dqTitleRenderer_Render();
