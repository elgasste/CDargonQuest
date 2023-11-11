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
   dqEventBattleRun,
   dqEventBattleExit
}
dqEventType_t;
