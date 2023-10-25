#pragma once

#include "common.h"

typedef struct
{
   sfTexture* playerTexture;
}
dqRenderData_t;

dqRenderData_t* dqRenderData;

void dqRenderData_Init();
void dqRenderData_Cleanup();
