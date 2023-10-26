#pragma once

#include "common.h"

typedef struct dqOverworldRenderer_t
{
   sfRectangleShape* darkTile;
   sfRectangleShape* lightTile;
   sfVector2f tilePosition;

   sfVector2f viewOffset;
   sfVector2f sideOffset;

   sfRectangleShape* occlusions[4];
}
dqOverworldRenderer_t;

dqOverworldRenderer_t* dqOverworldRenderer;

void dqOverworldRenderer_Init();
void dqOverworldRenderer_Cleanup();
void dqOverworldRenderer_Render();
void dqOverworldRenderer_RenderMap();
void dqOverworldRenderer_RenderEntities();
