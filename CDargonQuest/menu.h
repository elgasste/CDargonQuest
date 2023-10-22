#pragma once

#include "menu_option.h"

typedef struct
{
   dqMenuOption_t* options;
   unsigned int optionCount;
   unsigned int selectedOption;
}
dqMenu_t;
