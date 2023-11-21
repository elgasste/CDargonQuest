#include "render_data.h"
#include "render_config.h"
#include "game_data.h"
#include "player.h"

void dqRenderData_Init( dqEntityOverworldState_t* playerOverworldState )
{
   dqRenderData = (dqRenderData_t*)dqMalloc( sizeof( dqRenderData_t ), sfTrue );

   dqRenderData->overworldTilesetTexture = sfTexture_createFromFile( dqRenderConfig->overworldTilesetTexturePath, 0 );
   dqRenderData->dialogTilesetTexture = sfTexture_createFromFile( dqRenderConfig->dialogTilesetTexturePath, 0 );

   // TODO: these will come from a data file later
   dqRenderData->enemyTextures = dqMalloc( sizeof( sfTexture* ) * 4, sfTrue );
   dqRenderData->enemyTextures[0] = sfTexture_createFromFile( dqRenderConfig->enemyTextureSize0Path, 0 );
   dqRenderData->enemyTextures[1] = sfTexture_createFromFile( dqRenderConfig->enemyTextureSize1Path, 0 );
   dqRenderData->enemyTextures[2] = sfTexture_createFromFile( dqRenderConfig->enemyTextureSize2Path, 0 );
   dqRenderData->enemyTextures[3] = sfTexture_createFromFile( dqRenderConfig->enemyTextureSize3Path, 0 );

   dqRenderData->playerTexture = sfTexture_createFromFile( dqRenderConfig->playerTexturePath, 0 );
   dqRenderData->playerSprite = dqEntitySprite_Create( playerOverworldState, dqRenderData->playerTexture, 16, 16, 2, 0.25f );
}

void dqRenderData_Cleanup()
{
   int i;

   dqEntitySprite_Cleanup( dqRenderData->playerSprite );
   sfTexture_destroy( dqRenderData->playerTexture );

   for ( i = 0; i < 4; i++ )
   {
      sfTexture_destroy( dqRenderData->enemyTextures[i] );
   }

   dqFree( dqRenderData->enemyTextures, sizeof( sfTexture* ) * 4, sfTrue );

   sfTexture_destroy( dqRenderData->overworldTilesetTexture );

   dqFree( dqRenderData, sizeof( dqRenderData_t ), sfTrue );
}
