#pragma once

#include "common.h"

typedef struct
{
   char* textLine;
   sfRectangleShape* background;
   sfFont* font;
   sfText* text;
   sfVector2f textPosition;
   float lineSpacing;
   unsigned int currentFrameRateCache;
   unsigned int averageFrameRateCache;
   float refreshElapsedSeconds;
}
dqDiagnosticsRenderer_t;

dqDiagnosticsRenderer_t* dqDiagnosticsRenderer;

void dqDiagnosticsRenderer_Init();
void dqDiagnosticsRenderer_Cleanup();
void dqDiagnosticsRenderer_Render();
