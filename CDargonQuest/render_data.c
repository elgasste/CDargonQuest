#include "render_data.h"
#include "render_config.h"

void dqRenderData_Init()
{
   dqRenderData = (dqRenderData_t*)malloc( sizeof( dqRenderData_t ) );

#pragma warning ( suppress:6011 )
   dqRenderData->playerTexture = sfTexture_createFromFile( dqRenderConfig->playerTexturePath, NULL );
}

void dqRenderData_Cleanup()
{
   sfTexture_destroy( dqRenderData->playerTexture );

   SAFE_DELETE( dqRenderData );
}
