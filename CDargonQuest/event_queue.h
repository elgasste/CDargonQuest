#pragma once

#include "common.h"
#include "game_event.h"

#define MAX_GAME_EVENTS 100

typedef struct
{
   dqGameEvent_t queue [MAX_GAME_EVENTS];
   int front;
   int back;
}
dqEventQueue_t;

dqEventQueue_t* dqEventQueue;

void dqEventQueue_Init();
void dqEventQueue_Create();
void dqEventQueue_Cleanup();
sfBool dqEventQueue_IsEmpty();
void dqEventQueue_Push( dqGameEvent_t e );
dqGameEvent_t dqEventQueue_GetNext();
dqGameEvent_t dqEventQueue_PeekNext();
