#include "input_handler.h"
#include "input_state.h"
#include "game_config.h"
#include "render_config.h"
#include "title_input_handler.h"
#include "overworld_input_handler.h"
#include "game.h"

static void dqInputHandler_HandleCheat()
{
   // TODO: dqpass and dqexit
   char* cheat = dqInputHandler->cheatString;

   if ( !strcmp( cheat, "dqclip" ) )
   {
      dqGameConfig->noClipCheat = dqGameConfig->noClipCheat ? sfFalse : sfTrue;
   }

   dqInputHandler->cheatString[0] = '\0';
}

static void dqInputHandler_CheckCheats()
{
   int cheatStringLength, i, lastIndex, matchCount;
   static const char* cheats[] = {
      "dqclip",
      "dqpass",
      "dqexit"
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
      if ( cheats[i][lastIndex] != dqInputHandler->cheatString[lastIndex] )
      {
         matchCount--;
      }
      else if ( cheatStringLength == (int)strlen( cheats[i] ) )
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
   dqInputHandler = (dqInputHandler_t*)malloc( sizeof( dqInputHandler_t ) );
   CHECK_MALLOC( dqInputHandler )

   dqInputHandler->cheatString[0] = '\0';

   dqOverworldInputHandler_Init();
}

void dqInputHandler_Cleanup()
{
   SAFE_DELETE( dqInputHandler )

   dqOverworldInputHandler_Cleanup();
}

void dqInputHandler_HandleInput()
{
   if ( dqInputState_WasKeyPressed( sfKeyF8 ) )
   {
      dqRenderConfig->showDiagnostics = dqRenderConfig->showDiagnostics ? sfFalse : sfTrue;
   }

   dqInputHandler_CheckCheats();

   switch ( dqGame->state )
   {
      case dqStateTitle:
         dqTitleInputHandler_HandleInput();
         break;
      case dqStateOverworld:
         dqOverworldInputHandler_HandleInput();
         break;
   }
}
