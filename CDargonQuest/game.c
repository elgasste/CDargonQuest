#include "game.h"
#include "game_config.h"
#include "menu.h"
#include "render_config.h"
#include "game_data.h"
#include "window.h"
#include "clock.h"
#include "renderer.h"
#include "event_queue.h"
#include "entity.h"

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
   // TODO: this should all go in some kind of collision detection file
   dqEntity_t* player = dqGameData->player;

   if ( player->velocityX != 0 )
   {
      player->centerPosition.x += ( player->velocityX * dqClock->lastFrameSeconds );
      player->hitBoxPosition.x += ( player->velocityX * dqClock->lastFrameSeconds );
      player->velocityX = 0;
   }

   if ( player->velocityY != 0 )
   {
      player->centerPosition.y += ( player->velocityY * dqClock->lastFrameSeconds );
      player->hitBoxPosition.y += ( player->velocityY * dqClock->lastFrameSeconds );
      player->velocityY = 0;
   }

   if ( player->hitBoxPosition.x < 0 )
   {
      player->hitBoxPosition.x = 0;
      player->centerPosition.x = player->hitBoxSize.x / 2;
   }
   else if ( player->hitBoxPosition.x + player->hitBoxSize.x >= dqRenderConfig->screenWidth )
   {
      player->hitBoxPosition.x = dqRenderConfig->screenWidth - player->hitBoxSize.x;
      player->centerPosition.x = player->hitBoxPosition.x + ( player->hitBoxSize.x / 2 );
   }

   if ( player->hitBoxPosition.y < 0 )
   {
      player->hitBoxPosition.y = 0;
      player->centerPosition.y = player->hitBoxSize.y / 2;
   }
   else if ( player->hitBoxPosition.y + player->hitBoxSize.y >= dqRenderConfig->screenHeight )
   {
      player->hitBoxPosition.y = dqRenderConfig->screenHeight - player->hitBoxSize.y;
      player->centerPosition.y = player->hitBoxPosition.y + ( player->hitBoxSize.y / 2 );
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
