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

   sfFloatRect viewRect = { 0, 0, dqRenderConfig->screenWidth, dqRenderConfig->screenHeight };

   dqWindow = (dqWindow_t*)dqMalloc( sizeof( dqWindow_t ) );

   dqWindow->window = sfRenderWindow_create( videoMode, STR_WINDOW_TITLE, dqRenderConfig->windowStyle, NULL );

   dqWindow->view = sfView_createFromRect( viewRect );
   sfRenderWindow_setView( dqWindow->window, dqWindow->view );

   sfRenderWindow_setKeyRepeatEnabled( dqWindow->window, sfFalse );

   dqInputState_Init();
   dqInputHandler_Init();
}

void dqWindow_Cleanup()
{
   dqInputHandler_Cleanup();
   dqInputState_Cleanup();
   sfRenderWindow_close( dqWindow->window );
   sfRenderWindow_destroy( dqWindow->window );
   sfView_destroy( dqWindow->view );

   // MUFFINS: will this cause a crash?
   dqFree( dqWindow );
}

void dqWindow_HandleEvents()
{
   static sfEvent e;

   dqInputState_Reset();

   while ( sfRenderWindow_pollEvent( dqWindow->window, &e ) )
   {
      switch ( e.type )
      {
         case sfEvtClosed:
            dqEventQueue_Push( dqEventQuit, 0 );
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

void dqWindow_Clear()
{
   sfRenderWindow_clear( dqWindow->window, dqRenderConfig->windowClearColor );
}

void dqWindow_Display()
{
   sfRenderWindow_display( dqWindow->window );
}

void dqWindow_DrawRectangleShape( sfRectangleShape* rect )
{
   sfRenderWindow_drawRectangleShape( dqWindow->window, rect, NULL );
}

void dqWindow_DrawText( sfText* text )
{
   sfRenderWindow_drawText( dqWindow->window, text, NULL );
}

void dqWindow_DrawSprite( sfSprite* sprite )
{
   sfRenderWindow_drawSprite( dqWindow->window, sprite, NULL );
}

void dqWindow_DrawEntitySprite( dqEntitySprite_t* sprite )
{
   sfRenderWindow_drawSprite( dqWindow->window, sprite->sprite, NULL );
}
