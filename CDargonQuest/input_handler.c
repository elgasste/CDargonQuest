#include "input_handler.h"
#include "title_input_handler.h"
#include "game.h"

void dqInputHandler_HandleInput()
{
   switch ( dqGame->state )
   {
      case dqStateTitle:
         dqTitleInputHandler_HandleInput();
         break;
   }
}
