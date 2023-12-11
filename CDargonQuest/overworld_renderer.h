#if !defined( DQ_OVERWORLD_RENDERER_H )
#define DQ_OVERWORLD_RENDERER_H

#include "common.h"

typedef struct dqOverworldRenderer_t
{
   sfSprite* tileSprite;
   sfIntRect tileTextureRect;
   sfVector2f tilePosition;

   sfRectangleShape* occlusions[4];

   sfRectangleShape* passableRect;
   sfRectangleShape* impassableRect;
   sfRectangleShape* mapSwapRect;
   sfFont* cheatFont;
   sfText* cheatText;
   char cheatChars[64];
}
dqOverworldRenderer_t;

dqOverworldRenderer_t* dqOverworldRenderer;

void dqOverworldRenderer_Init();
void dqOverworldRenderer_Cleanup();
void dqOverworldRenderer_RenderMap();

#endif
