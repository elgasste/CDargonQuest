#include "render_data.h"
#include "render_config.h"
#include "game_data.h"
#include "player.h"

void dqRenderData_Init( dqEntityOverworldState_t* playerOverworldState )
{
   dqRenderData = (dqRenderData_t*)dqMalloc( sizeof( dqRenderData_t ) );

   dqRenderData->overworldTilesetTexture = sfTexture_createFromFile( dqRenderConfig->overworldTilesetTexturePath, NULL );
   dqRenderData->dialogTilesetTexture = sfTexture_createFromFile( dqRenderConfig->dialogTilesetTexturePath, NULL );

   dqRenderData->playerTexture = sfTexture_createFromFile( dqRenderConfig->playerTexturePath, NULL );
   dqRenderData->playerSprite = dqEntitySprite_Create( playerOverworldState, dqRenderData->playerTexture, 16, 16, 2, 0.25f );
}

void dqRenderData_Cleanup()
{
   dqEntitySprite_Cleanup( dqRenderData->playerSprite );
   sfTexture_destroy( dqRenderData->playerTexture );

   sfTexture_destroy( dqRenderData->overworldTilesetTexture );

   dqFree( dqRenderData );
}
