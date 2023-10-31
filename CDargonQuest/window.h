#pragma once

#include "common.h"
#include "entity_sprite.h"

typedef struct dqWindow_t
{
   sfRenderWindow* window;
   sfView* view;
}
dqWindow_t;

dqWindow_t* dqWindow;

void dqWindow_Init();
void dqWindow_Cleanup();
void dqWindow_HandleEvents();
void dqWindow_Clear();
void dqWindow_Display();
void dqWindow_DrawRectangleShape( sfRectangleShape* rect );
void dqWindow_DrawText( sfText* text );
void dqWindow_DrawSprite( sfSprite* sprite );
void dqWindow_DrawEntitySprite( dqEntitySprite_t* sprite );