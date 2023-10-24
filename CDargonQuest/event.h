#pragma once

#include "common.h"
#include "event_type.h"
#include "event_args.h"

typedef struct dqEvent_t
{
   dqEventType_t type;
   dqEventArgs_t args;
}
dqEvent_t;
