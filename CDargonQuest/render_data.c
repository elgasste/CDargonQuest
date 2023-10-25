#include "render_data.h"
#include "render_config.h"

void dqRenderData_Init( dqEntity_t* player )
{
   dqRenderData = (dqRenderData_t*)malloc( sizeof( dqRenderData_t ) );

#pragma warning ( suppress:6011 )
   dqRenderData->playerTexture = sfTexture_createFromFile( dqRenderConfig->playerTexturePath, NULL );
   dqRenderData->playerSprite = dqEntitySprite_Create( player, dqRenderData->playerTexture, 16, 16, 2, 0.25f );
}

void dqRenderData_Cleanup()
{
   dqEntitySprite_Cleanup( dqRenderData->playerSprite );
   sfTexture_destroy( dqRenderData->playerTexture );

   SAFE_DELETE( dqRenderData );
}
