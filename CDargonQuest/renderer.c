#include "renderer.h"
#include "window.h"
#include "render_config.h"
#include "title_renderer.h"
#include "game.h"

void dqRenderer_Init()
{
   dqTitleRenderer_Init();
}

void dqRenderer_Cleanup()
{
   dqTitleRenderer_Cleanup();
}

void dqRenderer_Render()
{
   sfRenderWindow_clear( dqWindow, dqRenderConfig->windowClearColor );

   switch ( dqGame->state )
   {
      case dqStateTitle:
         dqTitleRenderer_Render();
         break;
   }

   sfRenderWindow_display( dqWindow );
}
