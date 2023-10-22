#include "title_renderer.h"
#include "render_config.h"
#include "window.h"
#include "game.h"
#include "clock.h"

void dqTitleRenderer_Init()
{
   dqTitleRenderer = (dqTitleRenderer_t*)malloc( sizeof( dqTitleRenderer_t ) );

#pragma warning ( suppress:6011 )
   dqTitleRenderer->showCarat = sfTrue;
   dqTitleRenderer->caratElapsedSeconds = 0;
   dqTitleRenderer->selectedOptionCache = dqGame->titleMenu->selectedOption;
}

void dqTitleRenderer_Cleanup()
{
   SAFE_DELETE( dqTitleRenderer );
}

void dqTitleRenderer_Render()
{
   if ( dqGame->titleMenu->selectedOption != dqTitleRenderer->selectedOptionCache )
   {
      dqTitleRenderer->showCarat = sfTrue;
      dqTitleRenderer->caratElapsedSeconds = 0;
      dqTitleRenderer->selectedOptionCache = dqGame->titleMenu->selectedOption;
   }
   else
   {
      dqTitleRenderer->caratElapsedSeconds += dqClock->lastFrameSeconds;

      if ( dqTitleRenderer->caratElapsedSeconds >= dqRenderConfig->menuCaratBlinkRate )
      {
         dqTitleRenderer->showCarat = dqTitleRenderer->showCarat ? sfFalse : sfTrue;
         dqTitleRenderer->caratElapsedSeconds = 0;
      }
   }

   // TODO: actually draw the menu
   sfRenderWindow_clear( dqWindow, dqRenderConfig->windowClearColor );
   sfRenderWindow_display( dqWindow );
}
