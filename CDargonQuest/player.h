#if !defined( DQ_PLAYER_H )
#define DQ_PLAYER_H

#include "common.h"

typedef struct dqEntityOverworldState_t dqEntityOverworldState_t;
typedef struct dqBattleStats_t dqBattleStats_t;
typedef struct dqEntitySprite_t dqEntitySprite_t;

typedef struct dqPlayer_t
{
   char name[PLAYER_NAME_LENGTH];
   dqEntityOverworldState_t* overworldState;
   dqBattleStats_t* battleStats;
   dqEntitySprite_t* entitySprite;
}
dqPlayer_t;

dqPlayer_t* dqPlayer_Create();
void dqPlayer_Cleanup( dqPlayer_t* player );

#endif
