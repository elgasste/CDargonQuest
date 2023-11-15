#if !defined( DQ_LOG_H )
#define DQ_LOG_H

typedef struct _iobuf FILE;

typedef struct dqLog_t
{
   FILE* logFile;
}
dqLog_t;

dqLog_t* dqLog;

void dqLog_Init();
void dqLog_Cleanup();
void dqLog_Message( const char* message );
void dqLog_Error( const char* message );

#endif
