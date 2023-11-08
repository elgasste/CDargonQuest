#pragma once

#include "common.h"

typedef enum
{
   dqStateInit = 0,
   dqStateTitle,
   dqStateOverworld,
   dqStateOverworldTransition,
   dqStateBattleTransition,
   dqStateBattle,
   dqStateClosing
}
dqState_t;
