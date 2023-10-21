#include "window.h"
#include "render_config.h"
#include "game.h"

void dqWindow_Init()
{
   sfVideoMode videoMode =
   {
      dqRenderConfig->windowWidth,
      dqRenderConfig->windowHeight,
      dqRenderConfig->windowBPP
   };

   dqWindow = sfRenderWindow_create( videoMode, STR_WINDOW_TITLE, dqRenderConfig->windowStyle, NULL );
}

void dqWindow_Cleanup()
{
   sfRenderWindow_destroy( dqWindow );
}

void dqWindow_HandleEvents()
{
   static sfEvent e;

   while ( sfRenderWindow_pollEvent( dqWindow, &e ) )
   {
      switch ( e.type )
      {
         case sfEvtClosed:
            // TODO: raise some kind of "shutdown" game event instead of doing this
            dqGame->isRunning = sfFalse;
            sfRenderWindow_close( dqWindow );
            break;
         case sfEvtKeyPressed:
            // TODO: set up an input handler
            //_inputStateController->KeyPressed( e.key.code );
            break;
         case sfEvtKeyReleased:
            // TODO: set up an input handler
            //_inputStateController->KeyReleased( e.key.code );
            break;
      }
   }
}
