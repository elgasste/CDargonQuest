#pragma once

#include "common.h"
#include "event.h"

typedef struct dqEventQueue_t
{
   dqEvent_t queue [MAX_EVENTS];
   int front;
   int back;
}
dqEventQueue_t;

dqEventQueue_t* dqEventQueue;

void dqEventQueue_Init();
void dqEventQueue_Cleanup();
sfBool dqEventQueue_IsEmpty();
void dqEventQueue_Push( dqEventType_t type, int argCount, ... );
dqEvent_t* dqEventQueue_GetNext();
void dqEventQueue_Flush();
