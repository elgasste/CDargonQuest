#include "game.h"
#include "render_config.h"
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

   dqGame->titleMenu = (dqMenu_t*)malloc( sizeof( dqMenu_t ) );
#pragma warning ( suppress:6011 )
   dqGame->titleMenu->optionCount = 2;
   dqGame->titleMenu->selectedOption = 0;
   dqGame->titleMenu->options = (dqMenuOption_t*)malloc( sizeof( dqMenuOption_t ) * dqGame->titleMenu->optionCount );
#pragma warning ( suppress:6011 )
   dqGame->titleMenu->options[0].text = STR_TITLE_MENU_START;
   dqGame->titleMenu->options[0].eventType = dqEventStart;
   dqGame->titleMenu->options[1].text = STR_TITLE_MENU_QUIT;
   dqGame->titleMenu->options[1].eventType = dqEventQuit;

   dqRenderConfig_Init();
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
   dqRenderConfig_Cleanup();

   SAFE_DELETE( dqGame->titleMenu->options );
   SAFE_DELETE( dqGame->titleMenu );
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
