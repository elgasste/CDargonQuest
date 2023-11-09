#include "render_data.h"
#include "render_config.h"

void dqRenderData_Init( dqEntity_t* player )
{
   dqRenderData = (dqRenderData_t*)dqMalloc( sizeof( dqRenderData_t ) );

   dqRenderData->overworldTilesetTexture = sfTexture_createFromFile( dqRenderConfig->overworldTileTexturePath, NULL );

   dqRenderData->playerTexture = sfTexture_createFromFile( dqRenderConfig->playerTexturePath, NULL );
   dqRenderData->playerSprite = dqEntitySprite_Create( player, dqRenderData->playerTexture, 16, 16, 2, 0.25f );
}

void dqRenderData_Cleanup()
{
   dqEntitySprite_Cleanup( dqRenderData->playerSprite );
   sfTexture_destroy( dqRenderData->playerTexture );

   sfTexture_destroy( dqRenderData->overworldTilesetTexture );

   dqFree( dqRenderData );
}
