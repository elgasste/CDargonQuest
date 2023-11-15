#if !defined( DQ_OVERWORLD_INPUT_HANDLER_H )
#define DQ_OVERWORLD_INPUT_HANDLER_H

#include "common.h"
#include "direction.h"

typedef struct
{
   sfBool useDirectionCache;
   dqDirection directionCache;
}
dqOverworldInputHandler_t;

dqOverworldInputHandler_t* dqOverworldInputHandler;

void dqOverworldInputHandler_Init();
void dqOverworldInputHandler_Cleanup();
void dqOverworldInputHandler_HandleInput();

#endif
