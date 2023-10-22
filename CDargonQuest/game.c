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
   dqGame->state = stateInit;

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
   dqGame->state = statePlaying;

   while ( dqGame->isRunning )
   {
      dqClock_StartFrame();

      dqWindow_HandleEvents();
      dqGame_HandleEvents();
      dqGame_Tick();
      dqRenderer_Render();

      dqClock_EndFrame();
   }

   dqGame->state = stateClosing;
}

void dqGame_HandleEvents()
{
   // TODO
}

void dqGame_Tick()
{
   // TODO: update game objects.
}
