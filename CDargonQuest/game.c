#include "game.h"
#include "game_config.h"
#include "render_config.h"
#include "game_data.h"
#include "menu.h"
#include "render_data.h"
#include "window.h"
#include "clock.h"
#include "renderer.h"
#include "event_queue.h"
#include "entity.h"
#include "map.h"

void dqGame_Init()
{
   dqGame = (dqGame_t*)malloc( sizeof( dqGame_t ) );
   CHECK_MALLOC( dqGame )

   dqGame->isRunning = sfFalse;
   dqGame->state = dqStateInit;

   dqGameConfig_Init();
   dqRenderConfig_Init();
   dqGameData_Init();
   dqMenu_Init();
   dqRenderData_Init( dqGameData->player );
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
   dqMenu_Cleanup();
   dqRenderData_Cleanup();
   dqGameData_Cleanup();
   dqRenderConfig_Cleanup();
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
         case dqEventPointPlayer:
            dqGame_HandlePointPlayer( e );
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
   }

   if ( player->velocityY != 0 )
   {
      player->centerPosition.y += ( player->velocityY * dqClock->lastFrameSeconds );
      player->hitBoxPosition.y += ( player->velocityY * dqClock->lastFrameSeconds );
   }

   if ( player->hitBoxPosition.x < 0 )
   {
      player->hitBoxPosition.x = 0;
      player->centerPosition.x = player->hitBoxSize.x / 2;
   }
   else if ( player->hitBoxPosition.x + player->hitBoxSize.x >= dqGameData->maps[0].width )
   {
      player->hitBoxPosition.x = dqGameData->maps[0].width - player->hitBoxSize.x;
      player->centerPosition.x = player->hitBoxPosition.x + ( player->hitBoxSize.x / 2 );
   }

   if ( player->hitBoxPosition.y < 0 )
   {
      player->hitBoxPosition.y = 0;
      player->centerPosition.y = player->hitBoxSize.y / 2;
   }
   else if ( player->hitBoxPosition.y + player->hitBoxSize.y >= dqGameData->maps[0].height )
   {
      player->hitBoxPosition.y = dqGameData->maps[0].height - player->hitBoxSize.y;
      player->centerPosition.y = player->hitBoxPosition.y + ( player->hitBoxSize.y / 2 );
   }

   dqEntitySprite_Tick( dqRenderData->playerSprite );

   player->velocityX = 0;
   player->velocityY = 0;
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
   float velocityDelta = e->args.argList[1]
      ? dqGameConfig->playerVelocityDiagonal
      : dqGameConfig->playerVelocityStraight;

   switch ( direction )
   {
      case dqDirectionLeft:
         dqGameData->player->velocityX = -velocityDelta;
         break;
      case dqDirectionUp:
         dqGameData->player->velocityY = -velocityDelta;
         break;
      case dqDirectionRight:
         dqGameData->player->velocityX = velocityDelta;
         break;
      case dqDirectionDown:
         dqGameData->player->velocityY = velocityDelta;
         break;
   }
}

void dqGame_HandlePointPlayer( dqEvent_t* e )
{
   dqDirection direction = e->args.argList[0];

   switch ( direction )
   {
      case dqDirectionLeft:
         dqGameData->player->direction = dqDirectionLeft;
         break;
      case dqDirectionUp:
         dqGameData->player->direction = dqDirectionUp;
         break;
      case dqDirectionRight:
         dqGameData->player->direction = dqDirectionRight;
         break;
      case dqDirectionDown:
         dqGameData->player->direction = dqDirectionDown;
         break;
   }
}
