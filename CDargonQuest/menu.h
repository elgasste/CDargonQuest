#pragma once

#include "common.h"

typedef struct dqMenuOption_t dqMenuOption_t;

typedef struct dqMenu_t
{
   dqMenuOption_t* options;
   unsigned int optionCount;
   unsigned int selectedOption;

   sfVector2f optionsPos;
   unsigned int optionsWidth;
   int caratOffsetX;
}
dqMenu_t;

dqMenu_t* dqMenuTitle;
dqMenu_t* dqMenuBattleAction;

void dqMenu_Init();
void dqMenu_Cleanup();

void dqMenu_ScrollDown( dqMenu_t* menu );
void dqMenu_ScrollUp( dqMenu_t* menu );
void dqMenu_HandleDefaultInput( dqMenu_t* menu );
