#pragma once

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
