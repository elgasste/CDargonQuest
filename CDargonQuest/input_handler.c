#include "input_handler.h"
#include "input_state.h"
#include "render_config.h"
#include "title_input_handler.h"
#include "game.h"

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
   }
}
