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

   const char* menuFontFilePath;
   unsigned int menuFontSize;
   sfColor menuFontColor;
   const char* menuCaratText;
   float menuCaratOffsetX;
   float menuCaratBlinkRate;

   float titleMenuOffsetX;
   float titleMenuOffsetY;
}
dqRenderConfig_t;

dqRenderConfig_t* dqRenderConfig;

void dqRenderConfig_Init();
void dqRenderConfig_Cleanup();