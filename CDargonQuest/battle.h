#pragma once

#include "common.h"
#include "battle_state.h"

typedef struct dqBattle_t
{
   dqBattleState state;
   char resultMessage[128];
}
dqBattle_t;

dqBattle_t* dqBattle;

void dqBattle_Init();
void dqBattle_Cleanup();
void dqBattle_Generate();
void dqBattle_SetState( dqBattleState state );
void dqBattle_Attack();
void dqBattle_Run();
