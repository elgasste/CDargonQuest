#include "input_handler.h"
#include "input_state.h"
#include "game_config.h"
#include "render_config.h"
#include "overworld_input_handler.h"
#include "battle_input_handler.h"
#include "game.h"
#include "menu.h"
#include "renderer.h"

static void dqInputHandler_HandleCheat()
{
   char* cheat = dqInputHandler->cheatString;

   if ( !strcmp( cheat, "dqclip" ) )
   {
      dqGameConfig->noClipCheat = dqGameConfig->noClipCheat ? sfFalse : sfTrue;

      if ( dqGameConfig->noClipCheat )
      {
         dqLog_Message( "no-clip cheat on" );
      }
      else
      {
         dqLog_Message( "no-clip cheat off" );
      }
   }
   else if ( !strcmp( cheat, "dqinvis" ) )
   {
      dqGameConfig->invisibleCheat = dqGameConfig->invisibleCheat ? sfFalse : sfTrue;

      if ( dqGameConfig->invisibleCheat )
      {
         dqLog_Message( "invisibility cheat on" );
      }
      else
      {
         dqLog_Message( "invisibility cheat off" );
      }
   }
   else if ( !strcmp( cheat, "dqtilestat" ) )
   {
      dqGameConfig->tileStatCheat = dqGameConfig->tileStatCheat ? sfFalse : sfTrue;

      if ( dqGameConfig->tileStatCheat )
      {
         dqLog_Message( "map tile stats cheat on" );
      }
      else
      {
         dqLog_Message( "map tile stats cheat off" );
      }
   }
   else if ( !strcmp( cheat, "dqclear" ) )
   {
      dqGameConfig->noClipCheat = sfFalse;
      dqGameConfig->invisibleCheat = sfFalse;
      dqGameConfig->tileStatCheat = sfFalse;
      dqLog_Message( "cleared all cheats" );
   }

   dqInputHandler->cheatString[0] = '\0';
}

static void dqInputHandler_CheckCheats()
{
   int cheatStringLength, i, l, lastIndex, matchCount;
   static const char* cheats[] = {
      "dqclip",
      "dqinvis",
      "dqtilestat",
      "dqclear"
   };
   static int cheatCount = (int)( sizeof( cheats ) / sizeof( const char* ) );

   if ( !dqInputState->keyWasPressed )
   {
      return;
   }

   cheatStringLength = (int)strlen( dqInputHandler->cheatString );
   dqInputHandler->cheatString[cheatStringLength] = (char)( dqInputState->lastPressedKey + 97 );
   cheatStringLength++;
   dqInputHandler->cheatString[cheatStringLength] = '\0';

   matchCount = cheatCount;
   lastIndex = cheatStringLength - 1;

   for ( i = 0; i < cheatCount; i++ )
   {
      l = (int)strlen( cheats[i] );

      if ( lastIndex >= l || cheats[i][lastIndex] != dqInputHandler->cheatString[lastIndex] )
      {
         matchCount--;
      }
      else if ( cheatStringLength == l && !strcmp( cheats[i], dqInputHandler->cheatString ) )
      {
         dqInputHandler_HandleCheat();
         return;
      }
   }

   if ( matchCount == 0 )
   {
      dqInputHandler->cheatString[0] = '\0';
   }
}

void dqInputHandler_Init()
{
   dqInputHandler = (dqInputHandler_t*)dqMalloc( sizeof( dqInputHandler_t ) );

   dqInputHandler->cheatString[0] = '\0';

   dqOverworldInputHandler_Init();
}

void dqInputHandler_Cleanup()
{
   dqOverworldInputHandler_Cleanup();

   dqFree( dqInputHandler );
}

void dqInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyF8 ) )
   {
      dqRenderConfig->showDiagnostics = dqRenderConfig->showDiagnostics ? sfFalse : sfTrue;

      if ( dqRenderConfig->showDiagnostics )
      {
         dqLog_Message( "diagnostics view on" );
      }
      else
      {
         dqLog_Message( "diagnostics view off" );
      }
   }

   dqInputHandler_CheckCheats();

   if ( !dqRenderer->isBlockingInput )
   {
      switch ( dqGame->state )
      {
         case dqStateTitle:
            dqMenu_HandleInputDefault( dqMenuTitle );
            break;
         case dqStateOverworld:
            dqOverworldInputHandler_HandleInput();
            break;
         case dqStateBattle:
            dqBattleInputHandler_HandleInput();
            break;
      }
   }
}
