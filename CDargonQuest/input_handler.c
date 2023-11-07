#include "input_handler.h"
#include "input_state.h"
#include "render_config.h"
#include "title_input_handler.h"
#include "overworld_input_handler.h"
#include "game.h"

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
