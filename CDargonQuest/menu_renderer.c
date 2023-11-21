#include "menu_renderer.h"
#include "menu.h"
#include "menu_option.h"
#include "clock.h"
#include "render_config.h"
#include "dialog_renderer.h"

void dqMenuRenderer_Init()
{
   dqMenuRenderer = (dqMenuRenderer_t*)dqMalloc( sizeof( dqMenuRenderer_t ), sfTrue );
}

void dqMenuRenderer_Cleanup()
{
   dqFree( dqMenuRenderer, sizeof( dqMenuRenderer_t ), sfTrue );
}

void dqMenuRenderer_Render( dqMenu_t* menu )
{
   unsigned int i;
   static sfVector2f textPos;

   if ( menu != dqMenuRenderer->menuCache || menu->selectedOption != dqMenuRenderer->selectedOptionCache )
   {
      dqMenuRenderer->menuCache = menu;
      dqMenuRenderer->showCarat = sfTrue;
      dqMenuRenderer->caratElapsedSeconds = 0;
      dqMenuRenderer->selectedOptionCache = menu->selectedOption;
   }
   else
   {
      dqMenuRenderer->caratElapsedSeconds += dqClock->lastFrameSeconds;

      while ( dqMenuRenderer->caratElapsedSeconds >= dqRenderConfig->menuCaratBlinkRate )
      {
         TOGGLE_BOOL( dqMenuRenderer->showCarat );
         dqMenuRenderer->caratElapsedSeconds -= dqRenderConfig->menuCaratBlinkRate;
      }
   }

   for ( i = 0; i < menu->optionCount; i++ )
   {
      if ( dqMenuRenderer->showCarat && dqMenuRenderer->selectedOptionCache == i )
      {
         textPos.x = menu->optionsPos.x + ( menu->caratOffsetX * (int)( dqRenderConfig->dialogSpriteSize ) );
         textPos.y = menu->optionsPos.y + (float)( i * ( dqRenderConfig->dialogSpriteSize * 2 ) );
         dqDialogRenderer_DrawText( &textPos, dqRenderConfig->menuCaratText, 1 );
      }

      textPos.x = menu->optionsPos.x;
      textPos.y = menu->optionsPos.y + (float)( i * ( dqRenderConfig->dialogSpriteSize * 2 ) );
      dqDialogRenderer_DrawText( &textPos, menu->options[i].text, menu->optionsWidth );
   }
}
