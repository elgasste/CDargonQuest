#include "title_renderer.h"
#include "render_config.h"
#include "window.h"
#include "menu.h"
#include "menu_option.h"
#include "clock.h"

void dqTitleRenderer_Init()
{
   dqTitleRenderer = (dqTitleRenderer_t*)dqMalloc( sizeof( dqTitleRenderer_t ) );

   dqTitleRenderer->menuFont = sfFont_createFromFile( dqRenderConfig->menuFontFilePath );

   dqTitleRenderer->menuText = sfText_create();
   sfText_setFont( dqTitleRenderer->menuText, dqTitleRenderer->menuFont );
   sfText_setCharacterSize( dqTitleRenderer->menuText, dqRenderConfig->menuFontSize );
   sfText_setFillColor( dqTitleRenderer->menuText, dqRenderConfig->menuFontColor );
   dqTitleRenderer->menuTextPosition.x = dqRenderConfig->titleMenuOffsetX;

   dqTitleRenderer->menuCarat = sfText_create();
   sfText_setFont( dqTitleRenderer->menuCarat, dqTitleRenderer->menuFont );
   sfText_setCharacterSize( dqTitleRenderer->menuCarat, dqRenderConfig->menuFontSize );
   sfText_setFillColor( dqTitleRenderer->menuCarat, dqRenderConfig->menuFontColor );
   sfText_setString( dqTitleRenderer->menuCarat, dqRenderConfig->menuCaratText );
   dqTitleRenderer->menuCaratPosition.x = dqRenderConfig->titleMenuOffsetX + dqRenderConfig->menuCaratOffsetX;

   dqTitleRenderer->menuLineSpacing = sfFont_getLineSpacing( dqTitleRenderer->menuFont,
                                                             sfText_getCharacterSize( dqTitleRenderer->menuText ) );

   dqTitleRenderer->showCarat = sfTrue;
   dqTitleRenderer->caratElapsedSeconds = 0;
   dqTitleRenderer->selectedOptionCache = dqTitleMenu->selectedOption;
}

void dqTitleRenderer_Cleanup()
{
   sfText_destroy( dqTitleRenderer->menuCarat );
   sfText_destroy( dqTitleRenderer->menuText );
   sfFont_destroy( dqTitleRenderer->menuFont );

   dqFree( dqTitleRenderer );
}

void dqTitleRenderer_Render()
{
   unsigned int i;

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
         dqTitleRenderer->menuCaratPosition.y = dqRenderConfig->titleMenuOffsetY + ( i * dqTitleRenderer->menuLineSpacing );
         sfText_setPosition( dqTitleRenderer->menuCarat, dqTitleRenderer->menuCaratPosition );

         dqWindow_DrawText( dqTitleRenderer->menuCarat );
      }

      dqTitleRenderer->menuTextPosition.y = dqRenderConfig->titleMenuOffsetY + ( i * dqTitleRenderer->menuLineSpacing );
      sfText_setPosition( dqTitleRenderer->menuText, dqTitleRenderer->menuTextPosition );
      sfText_setString( dqTitleRenderer->menuText, dqTitleMenu->options[i].text );

      dqWindow_DrawText( dqTitleRenderer->menuText );
   }
}
