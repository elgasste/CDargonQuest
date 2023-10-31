#pragma once

#include "common.h"
#include "entity.h"

typedef struct
{
   dqEntity_t* entity;

   sfSprite* sprite;
   sfIntRect textureRect;
   sfVector2f hitBoxOffset;

   unsigned int currentFrame;
   unsigned int frameCount;

   float elapsedFrameSeconds;
   float frameTimeThreshold;
}
dqEntitySprite_t;

dqEntitySprite_t* dqEntitySprite_Create( dqEntity_t* entity,
                                         sfTexture* texture,
                                         int width,
                                         int height,
                                         unsigned int frameCount,
                                         float frameTimeThreshold );
void dqEntitySprite_Cleanup( dqEntitySprite_t* sprite );
void dqEntitySprite_Tick( dqEntitySprite_t* sprite );
