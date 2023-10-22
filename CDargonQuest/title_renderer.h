#pragma once

#include "common.h"

typedef struct
{
   sfFont* menuFont;
   sfText* menuText;
   sfText* menuCarat;
   sfVector2f menuTextPosition;
   sfVector2f menuCaratPosition;
   float menuLineSpacing;

   sfBool showCarat;
   float caratElapsedSeconds;
   unsigned int selectedOptionCache;
}
dqTitleRenderer_t;

dqTitleRenderer_t* dqTitleRenderer;

void dqTitleRenderer_Init();
void dqTitleRenderer_Cleanup();
void dqTitleRenderer_Render();
