#pragma once

#include "common.h"
#include "event.h"

#define MAX_EVENTS 100

typedef struct
{
   dqEventType_t queue [MAX_EVENTS];
   int front;
   int back;
}
dqEventQueue_t;

dqEventQueue_t* dqEventQueue;

void dqEventQueue_Init();
void dqEventQueue_Create();
void dqEventQueue_Cleanup();
sfBool dqEventQueue_IsEmpty();
void dqEventQueue_Push( dqEventType_t e );
dqEventType_t dqEventQueue_GetNext();
dqEventType_t dqEventQueue_PeekNext();
void dqEventQueue_Flush();
