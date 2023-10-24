#pragma once

#include "common.h"

typedef struct
{
   sfRectangleShape* darkTile;
   sfRectangleShape* lightTile;
   sfVector2f tilePosition;
}
dqOverworldRenderer_t;

dqOverworldRenderer_t* dqOverworldRenderer;

void dqOverworldRenderer_Init();
void dqOverworldRenderer_Cleanup();
void dqOverworldRenderer_Render();
