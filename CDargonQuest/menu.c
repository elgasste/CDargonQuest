#include "menu.h"

void dqMenu_ScrollDown( dqMenu_t* menu )
{
   menu->selectedOption++;

   if ( menu->selectedOption >= menu->optionCount )
   {
      menu->selectedOption = 0;
   }
}

void dqMenu_ScrollUp( dqMenu_t* menu )
{
   menu->selectedOption--;

   if ( menu->selectedOption <= 0 )
   {
      menu->selectedOption = menu->optionCount - 1;
   }
}
