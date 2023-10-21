#include "game.h"
#include "render_config.h"
#include "window.h"
#include "clock.h"
#include "renderer.h"

void dqGame_Init()
{
   dqGame_Create();

   dqRenderConfig_Init();
   dqWindow_Init();
   dqClock_Init();

   dqGame->isRunning = sfFalse;
   dqGame->state = STATE_INIT;
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
   dqClock_Cleanup();
   dqWindow_Cleanup();
   dqRenderConfig_Cleanup();

   SAFE_DELETE( dqGame )
}

void dqGame_Run()
{
   dqGame->isRunning = sfTrue;
   dqGame->state = STATE_PLAYING;

   while ( dqGame->isRunning )
   {
      dqClock_StartFrame();

      dqWindow_HandleEvents();
      // TODO: handle game events
      dqGame_Tick();
      dqRenderer_Render();

      dqClock_EndFrame();
   }

   dqGame->state = STATE_CLOSING;
}

void dqGame_Tick()
{
   // TODO: update game objects
}
