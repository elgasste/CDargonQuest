#pragma once

#include "common.h"

typedef struct dqMenu_t dqMenu_t;

typedef struct dqMenuRenderer_t
{
   sfBool showCarat;
   float caratElapsedSeconds;
   unsigned int selectedOptionCache;
   dqMenu_t* menuCache;
}
dqMenuRenderer_t;

dqMenuRenderer_t* dqMenuRenderer;

void dqMenuRenderer_Init();
void dqMenuRenderer_Cleanup();
void dqMenuRenderer_Render();
