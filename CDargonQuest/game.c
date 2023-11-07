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
#include "physics.h"
#include "map.h"
#include "transition_renderer.h"

static void dqGame_HandleStart()
{
   if ( dqGame->state == dqStateTitle )
   {
      dqEventQueue_Flush();
      dqGame->state = dqStateOverworld;
   }
}

static void dqGame_HandleQuit()
{
   // TODO: maybe ask about saving the game or whatnot
   dqEventQueue_Flush();
   dqGame->isRunning = sfFalse;
}

static void dqGame_HandleMovePlayer( dqEvent_t* e )
{
   dqDirection direction;
   float velocityDelta;

   if ( dqGame->state == dqStateOverworld )
   {
      direction = e->args.argList[0];
      velocityDelta = e->args.argList[1]
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
}

static void dqGame_HandlePointPlayer( dqEvent_t* e )
{
   dqDirection direction;

   if ( dqGame->state == dqStateOverworld )
   {
      direction = e->args.argList[0];

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
}

static void dqGame_HandleSwapMap( dqEvent_t* e )
{
   if ( dqGame->state == dqStateOverworld )
   {
      dqTransitionRenderer_Reset();

      dqGame->nextMapIndex = (unsigned int)( e->args.argList[0] );
      dqGame->nextMapTileIndex = (unsigned int)( e->args.argList[1] );

      dqGame->state = dqStateOverworldTransition;
   }
}

static void dqGame_HandleOverworldFadedOut()
{
   if ( dqGame->state == dqStateOverworldTransition )
   {
      dqMap_Swap( dqGame->nextMapIndex, dqGame->nextMapTileIndex );
   }
}

static void dqGame_HandleOverworldFadedIn()
{
   if ( dqGame->state == dqStateOverworldTransition )
   {
      dqGame->state = dqStateOverworld;
   }
}

static void dqGame_HandleEvents()
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
         case dqEventSwapMap:
            dqGame_HandleSwapMap( e );
            break;
         case dqEventOverworldFadedOut:
            dqGame_HandleOverworldFadedOut();
            break;
         case dqEventOverworldFadedIn:
            dqGame_HandleOverworldFadedIn();
            break;
      }
   }
}

static void dqGame_Tick()
{
   // TODO: eventually do this for all entities on the map
   dqPhysics_MoveEntity( dqGameData->player );
   dqEntitySprite_Tick( dqRenderData->playerSprite );
   dqPhysics_DecelerateEntity( dqGameData->player );

   dqMap_CheckSwap();
}

void dqGame_Init()
{
   dqGame = (dqGame_t*)malloc( sizeof( dqGame_t ) );
   CHECK_MALLOC( dqGame )

   dqGame->isRunning = sfFalse;
   dqGame->state = dqStateInit;

   dqGame->nextMapIndex = 0;
   dqGame->nextMapTileIndex = 0;

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
