#pragma once

#include "common.h"

typedef struct
{
   int minFrameRate;
   int maxFrameRate;

   unsigned int windowWidth;
   unsigned int windowHeight;
   unsigned int windowBPP;
   sfUint32 windowStyle;
   sfColor windowClearColor;
}
dqRenderConfig_t;

dqRenderConfig_t* dqRenderConfig;

void dqRenderConfig_Init();
void dqRenderConfig_Create();
void dqRenderConfig_Cleanup();