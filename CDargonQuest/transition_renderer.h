#pragma once

#include "common.h"

typedef struct dqTransitionRenderer_t
{
   float elapsedSeconds;

   sfBool fadingOut;
   sfBool fadingIn;

   sfBool raisedFadedOut;
   sfBool raisedFadedIn;

   sfRectangleShape* fadeRect;
}
dqTransitionRenderer_t;

dqTransitionRenderer_t* dqTransitionRenderer;

void dqTransitionRenderer_Init();
void dqTransitionRenderer_Cleanup();
void dqTransitionRenderer_Reset();
void dqTransitionRenderer_Render( sfBool black );
