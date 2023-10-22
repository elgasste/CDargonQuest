#pragma once

#include "event_type.h"
#include "event_args.h"

typedef struct
{
   dqEventType_t type;
   dqEventArgs_t args;
}
dqEvent_t;

int dqEvent_GetArgCount( dqEventType_t type );
