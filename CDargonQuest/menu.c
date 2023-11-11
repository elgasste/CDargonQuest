#include "menu.h"
#include "menu_option.h"
#include "render_config.h"
#include "input_state.h"
#include "event_queue.h"

void dqMenu_Init()
{
   dqMenuTitle = (dqMenu_t*)dqMalloc( sizeof( dqMenu_t ) );
   dqMenuTitle->optionsPos = dqRenderConfig->titleMenuOptionsPos;
   dqMenuTitle->optionsWidth = dqRenderConfig->titleMenuOptionsWidth;
   dqMenuTitle->caratOffsetX = dqRenderConfig->titleMenuCaratOffsetX;
   dqMenuTitle->optionCount = 2;
   dqMenuTitle->selectedOption = 0;
   dqMenuTitle->options = (dqMenuOption_t*)dqMalloc( sizeof( dqMenuOption_t ) * dqMenuTitle->optionCount );
   dqMenuTitle->options[0].text = STR_TITLE_MENU_START;
   dqMenuTitle->options[0].eventType = dqEventStart;
   dqMenuTitle->options[1].text = STR_TITLE_MENU_QUIT;
   dqMenuTitle->options[1].eventType = dqEventQuit;

   dqMenuBattleAction = (dqMenu_t*)dqMalloc( sizeof( dqMenu_t ) );
   dqMenuBattleAction->optionsPos = dqRenderConfig->battleActionMenuOptionsPos;
   dqMenuBattleAction->optionsWidth = dqRenderConfig->battleActionMenuOptionsWidth;
   dqMenuBattleAction->caratOffsetX = dqRenderConfig->battleActionMenuCaratOffsetX;
   dqMenuBattleAction->optionCount = 2;
   dqMenuBattleAction->selectedOption = 0;
   dqMenuBattleAction->options = (dqMenuOption_t*)dqMalloc( sizeof( dqMenuOption_t ) * dqMenuBattleAction->optionCount );
   dqMenuBattleAction->options[0].text = STR_BATTLE_MENU_ATTACK;
   dqMenuBattleAction->options[0].eventType = dqEventBattleAttack;
   dqMenuBattleAction->options[1].text = STR_BATTLE_MENU_RUN;
   dqMenuBattleAction->options[1].eventType = dqEventBattleRun;
}

void dqMenu_Cleanup()
{
   dqFree( dqMenuBattleAction->options );
   dqFree( dqMenuBattleAction );
   dqFree( dqMenuTitle->options );
   dqFree( dqMenuTitle );
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

void dqMenu_HandleDefaultInput( dqMenu_t* menu )
{
   if ( dqInputState_WasKeyPressed( sfKeyDown ) )
   {
      dqMenu_ScrollDown( menu );
   }
   else if ( dqInputState_WasKeyPressed( sfKeyUp ) )
   {
      dqMenu_ScrollUp( menu );
   }
   else if ( dqInputState_WasKeyPressed( sfKeyReturn ) )
   {
      dqEventQueue_Push( menu->options[menu->selectedOption].eventType, 0 );
   }
}
