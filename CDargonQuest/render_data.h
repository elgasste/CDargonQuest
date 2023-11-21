#if !defined( DQ_RENDER_DATA_H )
#define DQ_RENDER_DATA_H

#include "common.h"
#include "entity_sprite.h"

typedef struct
{
   sfTexture* overworldTilesetTexture;
   sfTexture* dialogTilesetTexture;

   sfTexture** enemyTextures;

   sfTexture* playerTexture;
   dqEntitySprite_t* playerSprite;
}
dqRenderData_t;

dqRenderData_t* dqRenderData;

void dqRenderData_Init( dqEntityOverworldState_t* playerOverworldState );
void dqRenderData_Cleanup();

#endif
