#pragma once

#include "common.h"
#include "event_type.h"

typedef struct dqMenuOption_t
{
   const char* text;
   dqEventType_t eventType;
}
dqMenuOption_t;
