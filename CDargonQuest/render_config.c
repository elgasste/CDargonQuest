#include "render_config.h"

void dqRenderConfig_Init()
{
   dqRenderConfig_Create();

   dqRenderConfig->minFrameRate = 20;
   dqRenderConfig->maxFrameRate = 60;

   dqRenderConfig->windowWidth = 1920;
   dqRenderConfig->windowHeight = 1280;
   dqRenderConfig->windowBPP = 32;
   dqRenderConfig->windowStyle = sfTitlebar | sfClose;
   dqRenderConfig->windowClearColor = sfBlack;
}

void dqRenderConfig_Create()
{
   dqRenderConfig = (dqRenderConfig_t*)malloc( sizeof( dqRenderConfig_t ) );

   if ( !dqRenderConfig )
   {
      dqError_ExitWithMessage( STR_ERROR_RENDERCONFIG_MEMORY );
   }
}

void dqRenderConfig_Cleanup()
{
   SAFE_DELETE( dqRenderConfig )
}