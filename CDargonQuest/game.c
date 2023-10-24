#include "game.h"
#include "game_config.h"
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

   dqGameConfig_Init();
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
   dqGameConfig_Cleanup();

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
            dqGame_HandleStart();
            break;
         case dqEventQuit:
            dqGame_HandleQuit();
            break;
         case dqEventMovePlayer:
            dqGame_HandleMovePlayer( e );
            break;
      }
   }
}

void dqGame_Tick()
{
   // TODO: collision detection
   if ( dqGameData->player->velocityX != 0 )
   {
      dqGameData->player->centerPosition.x += ( dqGameData->player->velocityX * dqClock->lastFrameSeconds );
      dqGameData->player->hitBoxPosition.x += ( dqGameData->player->velocityX * dqClock->lastFrameSeconds );
      dqGameData->player->velocityX = 0;
   }

   if ( dqGameData->player->velocityY != 0 )
   {
      dqGameData->player->centerPosition.y += ( dqGameData->player->velocityY * dqClock->lastFrameSeconds );
      dqGameData->player->hitBoxPosition.y += ( dqGameData->player->velocityY * dqClock->lastFrameSeconds );
      dqGameData->player->velocityY = 0;
   }
}

void dqGame_HandleStart()
{
   dqEventQueue_Flush();
   dqGame->state = dqStateOverworld;
}

void dqGame_HandleQuit()
{
   dqEventQueue_Flush();
   dqGame->isRunning = sfFalse;
}

void dqGame_HandleMovePlayer( dqEvent_t* e )
{
   dqDirection direction = e->args.argList[0];

   switch ( direction )
   {
      case dqDirectionLeft:
         dqGameData->player->velocityX = -dqGameConfig->maxPlayerVelocity;
         break;
      case dqDirectionUp:
         dqGameData->player->velocityY = -dqGameConfig->maxPlayerVelocity;
         break;
      case dqDirectionRight:
         dqGameData->player->velocityX = dqGameConfig->maxPlayerVelocity;
         break;
      case dqDirectionDown:
         dqGameData->player->velocityY = dqGameConfig->maxPlayerVelocity;
         break;
   }
}
