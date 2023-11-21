#include "render_data.h"
#include "render_config.h"
#include "game_data.h"

void dqRenderData_Init()
{
   dqRenderData = (dqRenderData_t*)dqMalloc( sizeof( dqRenderData_t ), sfTrue );

   dqRenderData->overworldTilesetTexture = dqTexture_CreateFromFile( dqRenderConfig->overworldTilesetTexturePath );
   dqRenderData->dialogTilesetTexture = dqTexture_CreateFromFile( dqRenderConfig->dialogTilesetTexturePath );

   // TODO: these will come from a data file later
   dqRenderData->enemyTextures = dqMalloc( sizeof( sfTexture* ) * 4, sfTrue );
   dqRenderData->enemyTextures[0] = dqTexture_CreateFromFile( dqRenderConfig->enemyTextureSize0Path );
   dqRenderData->enemyTextures[1] = dqTexture_CreateFromFile( dqRenderConfig->enemyTextureSize1Path );
   dqRenderData->enemyTextures[2] = dqTexture_CreateFromFile( dqRenderConfig->enemyTextureSize2Path );
   dqRenderData->enemyTextures[3] = dqTexture_CreateFromFile( dqRenderConfig->enemyTextureSize3Path );

   dqRenderData->playerTexture = dqTexture_CreateFromFile( dqRenderConfig->playerTexturePath );
}

void dqRenderData_Cleanup()
{
   int i;

   dqTexture_Destroy( dqRenderData->playerTexture );

   for ( i = 0; i < 4; i++ )
   {
      dqTexture_Destroy( dqRenderData->enemyTextures[i] );
   }

   dqFree( dqRenderData->enemyTextures, sizeof( sfTexture* ) * 4, sfTrue );

   dqTexture_Destroy( dqRenderData->dialogTilesetTexture );
   dqTexture_Destroy( dqRenderData->overworldTilesetTexture );

   dqFree( dqRenderData, sizeof( dqRenderData_t ), sfTrue );
}
