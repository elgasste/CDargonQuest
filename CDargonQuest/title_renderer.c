#include "title_renderer.h"
#include "render_config.h"
#include "dialog_renderer.h"
#include "window.h"
#include "menu.h"
#include "menu_option.h"
#include "clock.h"

void dqTitleRenderer_Init()
{
   dqTitleRenderer = (dqTitleRenderer_t*)dqMalloc( sizeof( dqTitleRenderer_t ) );

   dqTitleRenderer->showCarat = sfTrue;
   dqTitleRenderer->caratElapsedSeconds = 0;
   dqTitleRenderer->selectedOptionCache = dqTitleMenu->selectedOption;
}

void dqTitleRenderer_Cleanup()
{
   dqFree( dqTitleRenderer );
}

void dqTitleRenderer_Render()
{
   unsigned int i;
   static sfVector2f textPos;

   if ( dqTitleMenu->selectedOption != dqTitleRenderer->selectedOptionCache )
   {
      dqTitleRenderer->showCarat = sfTrue;
      dqTitleRenderer->caratElapsedSeconds = 0;
      dqTitleRenderer->selectedOptionCache = dqTitleMenu->selectedOption;
   }
   else
   {
      dqTitleRenderer->caratElapsedSeconds += dqClock->lastFrameSeconds;

      while ( dqTitleRenderer->caratElapsedSeconds >= dqRenderConfig->menuCaratBlinkRate )
      {
         dqTitleRenderer->showCarat = dqTitleRenderer->showCarat ? sfFalse : sfTrue;
         dqTitleRenderer->caratElapsedSeconds -= dqRenderConfig->menuCaratBlinkRate;
      }
   }

   for ( i = 0; i < dqTitleMenu->optionCount; i++ )
   {
      if ( dqTitleRenderer->showCarat && dqTitleRenderer->selectedOptionCache == i )
      {
         textPos.x = dqRenderConfig->titleMenuOptionsPos.x + ( dqRenderConfig->titleMenuCaratOffsetX * (int)( dqRenderConfig->dialogSpriteSize ) );
         textPos.y = dqRenderConfig->titleMenuOptionsPos.y + (float)( i * dqRenderConfig->dialogSpriteSize );
         dqDialogRenderer_DrawText( &textPos, dqRenderConfig->menuCaratText, 1 );
      }

      textPos.x = dqRenderConfig->titleMenuOptionsPos.x;
      textPos.y = dqRenderConfig->titleMenuOptionsPos.y + (float)( i * dqRenderConfig->dialogSpriteSize );
      dqDialogRenderer_DrawText( &textPos, dqTitleMenu->options[i].text, dqRenderConfig->titleMenuOptionsWidth );
   }
}
