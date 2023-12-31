#if !defined( DQ_GAME_H )
#define DQ_GAME_H

#include "common.h"
#include "state.h"
#include "event.h"

typedef struct dqGame_t
{
   sfBool isRunning;
   dqState_t state;
   dqState_t previousState;

   unsigned int nextMapIndex;
   unsigned int nextMapTileIndex;
}
dqGame_t;

dqGame_t* dqGame;

void dqGame_Init();
void dqGame_Cleanup();
void dqGame_Run();

#endif
