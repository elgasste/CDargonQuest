#include "render_data.h"
#include "render_config.h"
#include "game_data.h"
#include "player.h"

void dqRenderData_Init( dqEntityOverworldState_t* playerOverworldState )
{
   dqRenderData = (dqRenderData_t*)dqMalloc( sizeof( dqRenderData_t ), sfTrue );

   dqRenderData->overworldTilesetTexture = sfTexture_createFromFile( dqRenderConfig->overworldTilesetTexturePath, 0 );
   dqRenderData->dialogTilesetTexture = sfTexture_createFromFile( dqRenderConfig->dialogTilesetTexturePath, 0 );

   dqRenderData->playerTexture = sfTexture_createFromFile( dqRenderConfig->playerTexturePath, 0 );
   dqRenderData->playerSprite = dqEntitySprite_Create( playerOverworldState, dqRenderData->playerTexture, 16, 16, 2, 0.25f );
}

void dqRenderData_Cleanup()
{
   dqEntitySprite_Cleanup( dqRenderData->playerSprite );
   sfTexture_destroy( dqRenderData->playerTexture );

   sfTexture_destroy( dqRenderData->overworldTilesetTexture );

   dqFree( dqRenderData, sizeof( dqRenderData_t ), sfTrue );
}
