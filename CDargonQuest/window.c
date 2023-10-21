#include "window.h"
#include "render_config.h"
#include "game.h"
#include "input_state.h"

void dqWindow_Init()
{
   sfVideoMode videoMode =
   {
      dqRenderConfig->windowWidth,
      dqRenderConfig->windowHeight,
      dqRenderConfig->windowBPP
   };

   dqWindow = sfRenderWindow_create( videoMode, STR_WINDOW_TITLE, dqRenderConfig->windowStyle, NULL );

   dqInputState_Init();
}

void dqWindow_Cleanup()
{
   dqInputState_Cleanup();
   sfRenderWindow_destroy( dqWindow );
}

void dqWindow_HandleEvents()
{
   static sfEvent e;

   dqInputState_Reset();

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
            dqInputState_KeyPressed( e.key.code );
            break;
         case sfEvtKeyReleased:
            dqInputState_keyReleased( e.key.code );
            break;
      }
   }
}
