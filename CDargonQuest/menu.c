#include "menu.h"
#include "menu_option.h"

void dqMenu_Init()
{
   dqTitleMenu = (dqMenu_t*)malloc( sizeof( dqMenu_t ) );
#pragma warning ( suppress:6011 )
   dqTitleMenu->optionCount = 2;
   dqTitleMenu->selectedOption = 0;
   dqTitleMenu->options = (dqMenuOption_t*)malloc( sizeof( dqMenuOption_t ) * dqTitleMenu->optionCount );
#pragma warning ( suppress:6011 )
   dqTitleMenu->options[0].text = STR_TITLE_MENU_START;
   dqTitleMenu->options[0].eventType = dqEventStart;
   dqTitleMenu->options[1].text = STR_TITLE_MENU_QUIT;
   dqTitleMenu->options[1].eventType = dqEventQuit;
}

void dqMenu_Cleanup()
{
   SAFE_DELETE( dqTitleMenu->options );
   SAFE_DELETE( dqTitleMenu );
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
