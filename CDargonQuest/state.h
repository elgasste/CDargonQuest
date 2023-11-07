#pragma once

#include "common.h"

typedef enum
{
   dqStateInit = 0,
   dqStateTitle,
   dqStateOverworld,
   dqStateOverworldTransition,
   dqStateClosing
}
dqState_t;
