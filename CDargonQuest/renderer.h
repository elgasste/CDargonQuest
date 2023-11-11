#pragma once

#include "common.h"

typedef struct dqRenderer_t
{
   sfBool isBlockingInput;
}
dqRenderer_t;

dqRenderer_t* dqRenderer;

void dqRenderer_Init();
void dqRenderer_Cleanup();
void dqRenderer_Render();
void dqRenderer_BlockInput();
void dqRenderer_UnblockInput();
