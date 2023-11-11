#pragma once

typedef enum
{
   dqEventStart = 0,
   dqEventQuit,

   dqEventMovePlayer,
   dqEventPointPlayer,

   dqEventSwapMap,

   dqEventFadedOut,
   dqEventFadedIn,

   dqEventEncounter,

   dqEventBattleAttack,
   dqEventBattleExit
}
dqEventType_t;
