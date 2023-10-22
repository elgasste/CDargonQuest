#pragma once

#include "common.h"
#include "menu_option.h"

typedef struct
{
   dqMenuOption_t* options;
   unsigned int optionCount;
   unsigned int selectedOption;
}
dqMenu_t;

dqMenu_t* dqTitleMenu;

void dqMenu_Init();
void dqMenu_Cleanup();

void dqMenu_ScrollDown( dqMenu_t* menu );
void dqMenu_ScrollUp( dqMenu_t* menu );
