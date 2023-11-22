#if !defined( DQ_EVENT_TYPE_H )
#define DQ_EVENT_TYPE_H

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
   dqEventBattleSpell,
   dqEventBattleItem,
   dqEventBattleGuard,
   dqEventBattleRun,
   dqEventBattleExit
}
dqEventType_t;

#endif
