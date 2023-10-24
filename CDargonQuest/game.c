#include "game.h"
#include "menu.h"
#include "render_config.h"
#include "game_data.h"
#include "window.h"
#include "clock.h"
#include "renderer.h"
#include "event_queue.h"

void dqGame_Init()
{
   dqGame = (dqGame_t*)malloc( sizeof( dqGame_t ) );

#pragma warning ( suppress:6011 )
   dqGame->isRunning = sfFalse;
   dqGame->state = dqStateInit;

   dqMenu_Init();
   dqRenderConfig_Init();
   dqGameData_Init();
   dqWindow_Init();
   dqRenderer_Init();
   dqClock_Init();
   dqEventQueue_Init();
}

void dqGame_Cleanup()
{
   dqEventQueue_Cleanup();
   dqClock_Cleanup();
   dqRenderer_Cleanup();
   dqWindow_Cleanup();
   dqGameData_Cleanup();
   dqRenderConfig_Cleanup();
   dqMenu_Cleanup();

   SAFE_DELETE( dqGame )
}

void dqGame_Run()
{
   dqGame->isRunning = sfTrue;
   dqGame->state = dqStateTitle;

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
         case dqEventStart:
            dqGame_Start();
            break;
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

void dqGame_Start()
{
   dqEventQueue_Flush();
   dqGame->state = dqStateOverworld;
}

void dqGame_Quit()
{
   dqEventQueue_Flush();
   dqGame->isRunning = sfFalse;
}
