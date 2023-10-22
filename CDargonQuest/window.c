#include "window.h"
#include "render_config.h"
#include "game.h"
#include "input_state.h"
#include "input_handler.h"
#include "event_queue.h"

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
   sfRenderWindow_close( dqWindow );
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
            dqEventQueue_Push( eventQuit );
            break;
         case sfEvtKeyPressed:
            dqInputState_SetKeyPressed( e.key.code );
            break;
         case sfEvtKeyReleased:
            dqInputState_SetKeyReleased( e.key.code );
            break;
      }
   }

   dqInputHandler_HandleInput();
}
