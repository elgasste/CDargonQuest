#include "renderer.h"
#include "title_renderer.h"
#include "game.h"

void dqRenderer_Render()
{
   switch ( dqGame->state )
   {
      case dqStateTitle:
         dqTitleRenderer_Render();
         break;
   }
}
