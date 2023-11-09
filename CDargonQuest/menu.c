#include "menu.h"
#include "menu_option.h"

void dqMenu_Init()
{
   dqTitleMenu = (dqMenu_t*)dqMalloc( sizeof( dqMenu_t ) );
   dqTitleMenu->optionCount = 2;
   dqTitleMenu->selectedOption = 0;
   dqTitleMenu->options = (dqMenuOption_t*)dqMalloc( sizeof( dqMenuOption_t ) * dqTitleMenu->optionCount );
   dqTitleMenu->options[0].text = STR_TITLE_MENU_START;
   dqTitleMenu->options[0].eventType = dqEventStart;
   dqTitleMenu->options[1].text = STR_TITLE_MENU_QUIT;
   dqTitleMenu->options[1].eventType = dqEventQuit;
}

void dqMenu_Cleanup()
{
   dqFree( dqTitleMenu->options );
   dqFree( dqTitleMenu );
}

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
   if ( menu->selectedOption == 0 )
   {
      menu->selectedOption = menu->optionCount - 1;
   }
   else
   {
      menu->selectedOption--;
   }
}
