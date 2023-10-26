#pragma once

#include "common.h"
#include "entity_sprite.h"

typedef struct
{
   sfTexture* playerTexture;
   dqEntitySprite_t* playerSprite;
}
dqRenderData_t;

dqRenderData_t* dqRenderData;

void dqRenderData_Init( dqEntity_t* player );
void dqRenderData_Cleanup();
