#pragma once

#include "common.h"

typedef struct dqDialogRenderer_t
{
   sfSprite* sprite;
   sfIntRect textureRect;
}
dqDialogRenderer_t;

dqDialogRenderer_t* dqDialogRenderer;

void dqDialogRenderer_Init();
void dqDialogRenderer_Cleanup();
void dqDialogRenderer_DrawBorder( sfVector2f pos, unsigned int width, unsigned int height );
