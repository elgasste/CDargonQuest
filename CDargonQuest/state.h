#if !defined( DQ_STATE_H )
#define DQ_STATE_H

typedef enum
{
   dqStateInit = 0,
   dqStateTitle,
   dqStateOverworld,
   dqStateOverworldTransition,
   dqStateBattleTransitionIn,
   dqStateBattleTransitionOut,
   dqStateBattle,
   dqStateClosing
}
dqState_t;

#endif
