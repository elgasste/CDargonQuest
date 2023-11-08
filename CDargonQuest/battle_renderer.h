#pragma once

#include "common.h"

typedef struct
{
   int garbo;
}
dqBattleRenderer_t;

dqBattleRenderer_t* dqBattleRenderer;

void dqBattleRenderer_Init();
void dqBattleRenderer_Cleanup();
void dqBattleRenderer_Render();
