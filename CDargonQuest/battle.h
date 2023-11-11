#pragma once

#include "common.h"
#include "battle_state.h"

typedef struct dqBattle_t
{
   dqBattleState state;
}
dqBattle_t;

dqBattle_t* dqBattle;

void dqBattle_Init();
void dqBattle_Cleanup();
void dqBattle_Generate();
void dqBattle_SetState( dqBattleState state );
