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
   dqEventOverworldFadedIn
}
dqEventType_t;
