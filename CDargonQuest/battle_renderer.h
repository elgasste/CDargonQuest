#if !defined( DQ_BATTLE_RENDERER_H )
#define DQ_BATTLE_RENDERER_H

#include "common.h"

typedef struct
{
   int garbo;
}
dqBattleRenderer_t;

dqBattleRenderer_t* dqBattleRenderer;

void dqBattleRenderer_Init();
void dqBattleRenderer_Cleanup();
void dqBattleRenderer_Render();

#endif
