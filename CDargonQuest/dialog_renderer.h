#pragma once

#include "common.h"

typedef struct dqDialogRenderer_t
{
   sfBool isScrolling;
   sfBool hasScrolled;
   float scrollElapsedSeconds;
   unsigned int scrollCharCount;

   sfSprite* sprite;
   sfIntRect textureRect;
}
dqDialogRenderer_t;

dqDialogRenderer_t* dqDialogRenderer;

void dqDialogRenderer_Init();
void dqDialogRenderer_Cleanup();
void dqDialogRenderer_ResetScroll();
void dqDialogRenderer_DrawBorder( sfVector2f* pos, unsigned int width, unsigned int height );
void dqDialogRenderer_DrawText( sfVector2f* pos, const char* text, unsigned int width );
void dqDialogRenderer_ScrollText( sfVector2f* pos, const char* text, unsigned int width );
