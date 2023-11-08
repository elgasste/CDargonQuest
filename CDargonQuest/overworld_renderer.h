#pragma once

#include "common.h"

typedef struct dqOverworldRenderer_t
{
   sfSprite* tileSprite;
   sfIntRect tileTextureRect;
   sfVector2f tilePosition;

   sfVector2f viewOffset;
   sfVector2f sideOffset;

   sfRectangleShape* occlusions[4];

   sfRectangleShape* passableRect;
   sfRectangleShape* impassableRect;
   sfRectangleShape* mapSwapRect;
   sfFont* encounterRateFont;
   sfText* encounterRateText;
   char encounterRateChars[32];
}
dqOverworldRenderer_t;

dqOverworldRenderer_t* dqOverworldRenderer;

void dqOverworldRenderer_Init();
void dqOverworldRenderer_Cleanup();
void dqOverworldRenderer_RenderMap();
void dqOverworldRenderer_RenderEntities();
