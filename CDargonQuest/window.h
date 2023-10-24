#pragma once

#include "common.h"

typedef struct
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