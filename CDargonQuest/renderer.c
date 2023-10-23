#include "renderer.h"
#include "window.h"
#include "render_config.h"
#include "diagnostics_renderer.h"
#include "title_renderer.h"
#include "overworld_renderer.h"
#include "game.h"

void dqRenderer_Init()
{
   dqDiagnosticsRenderer_Init();
   dqTitleRenderer_Init();
}

void dqRenderer_Cleanup()
{
   dqTitleRenderer_Cleanup();
   dqDiagnosticsRenderer_Cleanup();
}

void dqRenderer_Render()
{
   sfRenderWindow_clear( dqWindow, dqRenderConfig->windowClearColor );

   switch ( dqGame->state )
   {
      case dqStateTitle:
         dqTitleRenderer_Render();
         break;
      case dqStateOverworld:
         dqOverworldRenderer_Render();
         break;
   }

   if ( dqRenderConfig->showDiagnostics )
   {
      dqDiagnosticsRenderer_Render();
   }

   sfRenderWindow_display( dqWindow );
}
