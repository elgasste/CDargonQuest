#if !defined( DQ_RENDER_DATA_H )
#define DQ_RENDER_DATA_H

#include "common.h"

typedef struct dqEntityOverworldState_t dqEntityOverworldState_t;

typedef struct
{
   sfTexture* overworldTilesetTexture;
   sfTexture* dialogTilesetTexture;
   sfTexture** enemyTextures;
   sfTexture* playerTexture;
}
dqRenderData_t;

dqRenderData_t* dqRenderData;

void dqRenderData_Init();
void dqRenderData_Cleanup();

#endif
