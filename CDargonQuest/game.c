#include "game.h"
#include "render_config.h"
#include "window.h"
#include "clock.h"
#include "renderer.h"
#include "event_queue.h"

void dqGame_Init()
{
   dqGame_Create();

   dqGame->isRunning = sfFalse;
   dqGame->state = dqStateInit;

   dqRenderConfig_Init();
   dqWindow_Init();
   dqClock_Init();
   dqEventQueue_Init();
}

void dqGame_Create()
{
   dqGame = (dqGame_t*)malloc( sizeof( dqGame_t ) );

   if ( !dqGame )
   {
      dqError_ExitWithMessage( STR_ERROR_GAME_MEMORY );
   }
}

void dqGame_Cleanup()
{
   dqEventQueue_Cleanup();
   dqClock_Cleanup();
   dqWindow_Cleanup();
   dqRenderConfig_Cleanup();

   SAFE_DELETE( dqGame )
}

void dqGame_Run()
{
   dqGame->isRunning = sfTrue;
   dqGame->state = dqStatePlaying;

   while ( dqGame->isRunning )
   {
      dqClock_StartFrame();

      dqGame_HandleEvents();
      dqGame_Tick();
      dqRenderer_Render();

      dqClock_EndFrame();
   }

   dqGame->state = dqStateClosing;
}

void dqGame_HandleEvents()
{
   dqEvent_t* e;

   dqWindow_HandleEvents();

   while ( !dqEventQueue_IsEmpty() )
   {
      e = dqEventQueue_GetNext();

      switch ( e->type )
      {
         case dqEventQuit:
            dqGame_Quit();
            break;
      }
   }
}

void dqGame_Tick()
{
   // TODO: update game objects.
}

void dqGame_Quit()
{
   dqEventQueue_Flush();
   dqGame->isRunning = sfFalse;
}
