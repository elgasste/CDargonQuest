#pragma once

#include "common.h"

typedef struct dqEntityOverworldState_t dqEntityOverworldState_t;

typedef struct
{
   dqEntityOverworldState_t* entityOverworldState;

   sfSprite* sprite;
   sfIntRect textureRect;
   sfVector2f hitBoxOffset;

   unsigned int currentFrame;
   unsigned int frameCount;

   float elapsedFrameSeconds;
   float frameTimeThreshold;
}
dqEntitySprite_t;

dqEntitySprite_t* dqEntitySprite_Create( dqEntityOverworldState_t* entityOverworldState,
                                         sfTexture* texture,
                                         int width,
                                         int height,
                                         unsigned int frameCount,
                                         float frameTimeThreshold );
void dqEntitySprite_Cleanup( dqEntitySprite_t* sprite );
void dqEntitySprite_Tick( dqEntitySprite_t* sprite );
