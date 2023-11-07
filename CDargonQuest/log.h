#pragma once

#include "common.h"

typedef struct dqLog_t
{
   FILE* logFile;
}
dqLog_t;

dqLog_t* dqLog;

void dqLog_Init();
void dqLog_Cleanup();
void dqLog_Message( const char* message );
