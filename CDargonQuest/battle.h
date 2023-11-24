#if !defined( DQ_BATTLE_H )
#define DQ_BATTLE_H

#include "common.h"
#include "battle_state.h"

typedef struct dqEnemy_t dqEnemy_t;

typedef struct dqBattle_t
{
   dqBattleState state;

   char introMessage[128];
   char resultMessage[128];

   dqEnemy_t* enemy;
}
dqBattle_t;

dqBattle_t* dqBattle;

void dqBattle_Init();
void dqBattle_Cleanup();
void dqBattle_Reset();
void dqBattle_Generate();
void dqBattle_SetState( dqBattleState state );
void dqBattle_Attack();
void dqBattle_CastSpell();
void dqBattle_UseItem();
void dqBattle_Guard();
void dqBattle_Run();

#endif
