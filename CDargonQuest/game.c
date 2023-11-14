#include "game.h"
#include "game_config.h"
#include "log.h"
#include "random.h"
#include "render_config.h"
#include "game_data.h"
#include "menu.h"
#include "render_data.h"
#include "window.h"
#include "clock.h"
#include "renderer.h"
#include "event_queue.h"
#include "player.h"
#include "entity_overworld_state.h"
#include "physics.h"
#include "map.h"
#include "battle.h"
#include "transition_renderer.h"
#include "dialog_renderer.h"

static void dqGame_HandleEvents();
static void dqGame_Tick();
static void dqGame_SetState( dqState_t state );
static void dqGame_HandleStart();
static void dqGame_HandleQuit();
static void dqGame_HandleMovePlayer( dqEvent_t* e );
static void dqGame_HandlePointPlayer( dqEvent_t* e );
static void dqGame_HandleSwapMap( dqEvent_t* e );
static void dqGame_HandleFadedOut();
static void dqGame_HandleFadedIn();
static void dqGame_HandleEncounter();
static void dqGame_HandleBattleAttack();
static void dqGame_HandleBattleRun();
static void dqGame_HandleBattleExit();

void dqGame_Init()
{
   dqGame = (dqGame_t*)dqMalloc( sizeof( dqGame_t ) );

   dqGame->isRunning = sfFalse;
   dqGame->state = dqStateInit;
   dqGame->previousState = dqStateInit;

   dqGame->nextMapIndex = 0;
   dqGame->nextMapTileIndex = 0;

   dqGameConfig_Init();
   dqLog_Init();

   dqLog_Message( "loading game objects" );

   dqRandom_Init();
   dqRenderConfig_Init();
   dqGameData_Init();
   dqMenu_Init();
   dqRenderData_Init( dqGameData->player->overworldState );
   dqWindow_Init();
   dqRenderer_Init();
   dqClock_Init();
   dqEventQueue_Init();
   dqBattle_Init();

   dqLog_Message( "game objects loaded" );
}

void dqGame_Cleanup()
{
   dqBattle_Cleanup();
   dqEventQueue_Cleanup();
   dqClock_Cleanup();
   dqRenderer_Cleanup();
   dqWindow_Cleanup();
   dqMenu_Cleanup();
   dqRenderData_Cleanup();
   dqGameData_Cleanup();
   dqRenderConfig_Cleanup();
   dqGameConfig_Cleanup();

   dqLog_Message( "game objects cleaned up" );
   dqLog_Cleanup();

   dqFree( dqGame );
}

void dqGame_Run()
{
   dqLog_Message( "game loop starting" );
   dqGame_SetState( dqStateTitle );
   dqGame->isRunning = sfTrue;

   while ( dqGame->isRunning )
   {
      dqClock_StartFrame();

      dqGame_HandleEvents();
      dqGame_Tick();
      dqRenderer_Render();

      dqClock_EndFrame();
   }

   dqLog_Message( "game loop ended" );
   dqGame_SetState( dqStateClosing );
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
         case dqEventFadedOut:
            dqGame_HandleFadedOut();
            break;
         case dqEventFadedIn:
            dqGame_HandleFadedIn();
            break;
         case dqEventEncounter:
            dqGame_HandleEncounter();
            break;
         case dqEventBattleAttack:
            dqGame_HandleBattleAttack();
            break;
         case dqEventBattleRun:
            dqGame_HandleBattleRun();
            break;
         case dqEventBattleExit:
            dqGame_HandleBattleExit();
            break;
      }
   }
}

static void dqGame_Tick()
{
   if ( dqGame->state == dqStateOverworld )
   {
      // TODO: eventually do this for all entities on the map
      dqPhysics_MoveEntity( dqGameData->player->overworldState );
      dqEntitySprite_Tick( dqRenderData->playerSprite );
      dqPhysics_DecelerateEntity( dqGameData->player->overworldState );

      dqMap_CheckSwap();
      dqMap_CheckEncounter();
   }
}

static void dqGame_SetState( dqState_t state )
{
   dqGame->previousState = dqGame->state;
   dqGame->state = state;
}

static void dqGame_HandleStart()
{
   if ( dqGame->state == dqStateTitle )
   {
      dqEventQueue_Flush();
      dqGame_SetState( dqStateOverworld );
   }
}

static void dqGame_HandleQuit()
{
   // TODO: maybe ask about saving the game or whatnot
   dqEventQueue_Flush();
   dqGame->isRunning = sfFalse;
   dqLog_Message( "quitting game" );
}

static void dqGame_HandleMovePlayer( dqEvent_t* e )
{
   dqDirection direction;
   float velocityDelta;
   dqEntityOverworldState_t* playerState = dqGameData->player->overworldState;

   if ( dqGame->state == dqStateOverworld )
   {
      direction = e->args.argList[0];
      velocityDelta = e->args.argList[1]
         ? dqGameConfig->playerVelocityDiagonal
         : dqGameConfig->playerVelocityStraight;

      switch ( direction )
      {
         case dqDirectionLeft:
            playerState->velocityX = -velocityDelta;
            break;
         case dqDirectionUp:
            playerState->velocityY = -velocityDelta;
            break;
         case dqDirectionRight:
            playerState->velocityX = velocityDelta;
            break;
         case dqDirectionDown:
            playerState->velocityY = velocityDelta;
            break;
      }
   }
}

static void dqGame_HandlePointPlayer( dqEvent_t* e )
{
   dqDirection direction;
   dqEntityOverworldState_t* playerState = dqGameData->player->overworldState;

   if ( dqGame->state == dqStateOverworld )
   {
      direction = e->args.argList[0];

      switch ( direction )
      {
         case dqDirectionLeft:
            playerState->direction = dqDirectionLeft;
            break;
         case dqDirectionUp:
            playerState->direction = dqDirectionUp;
            break;
         case dqDirectionRight:
            playerState->direction = dqDirectionRight;
            break;
         case dqDirectionDown:
            playerState->direction = dqDirectionDown;
            break;
      }
   }
}

static void dqGame_HandleSwapMap( dqEvent_t* e )
{
   if ( dqGame->state == dqStateOverworld )
   {
      dqGame->nextMapIndex = (unsigned int)( e->args.argList[0] );
      dqGame->nextMapTileIndex = (unsigned int)( e->args.argList[1] );

      dqEventQueue_Flush();
      dqTransitionRenderer_Reset();
      dqGame_SetState( dqStateOverworldTransition );
   }
}

static void dqGame_HandleFadedOut()
{
   if ( dqGame->state == dqStateOverworldTransition )
   {
      dqMap_Swap( dqGame->nextMapIndex, dqGame->nextMapTileIndex );
   }
   else if ( dqGame->state == dqStateBattleTransitionIn )
   {
      dqBattle_Generate();
   }
}

static void dqGame_HandleFadedIn()
{
   if ( dqGame->state == dqStateOverworldTransition || dqGame->state == dqStateBattleTransitionOut )
   {
      dqGame_SetState( dqStateOverworld );
   }
   else if ( dqGame->state == dqStateBattleTransitionIn )
   {
      dqGame_SetState( dqStateBattle );
   }
}

static void dqGame_HandleEncounter()
{
   if ( dqGame->state == dqStateOverworld )
   {
      dqEventQueue_Flush();
      dqTransitionRenderer_Reset();
      dqGame_SetState( dqStateBattleTransitionIn );
   }
}

static void dqGame_HandleBattleAttack()
{
   if ( dqGame->state == dqStateBattle )
   {
      dqBattle_Attack();
   }
}

static void dqGame_HandleBattleRun()
{
   if ( dqGame->state == dqStateBattle )
   {
      dqBattle_Run();
   }
}

static void dqGame_HandleBattleExit()
{
   if ( dqGame->state == dqStateBattle )
   {
      dqEventQueue_Flush();
      dqTransitionRenderer_Reset();
      dqGame_SetState( dqStateBattleTransitionOut );
   }
}
