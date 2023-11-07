#pragma once

#include "common.h"

typedef enum
{
   dqEventStart = 0,
   dqEventQuit,

   dqEventMovePlayer,
   dqEventPointPlayer,

   dqEventSwapMap,

   dqEventOverworldFadedOut,
   dqEventOverworldFadedIn,

   dqEventEncounter
}
dqEventType_t;
