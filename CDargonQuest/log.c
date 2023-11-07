#include "log.h"
#include "game_config.h"

void dqLog_Init()
{
   dqLog = (dqLog_t*)malloc( sizeof( dqLog_t ) );
   CHECK_MALLOC( dqLog )

   if ( fopen_s( &( dqLog->logFile ), dqGameConfig->logFileName, "w" ) )
   {
      dqError_ExitWithMessageNoLog( STR_ERROR_LOG_FILE_OPEN );
   }
}

void dqLog_Cleanup()
{
   fclose( dqLog->logFile );

   SAFE_DELETE( dqLog )
}

void dqLog_Message( const char* message )
{
   if ( fprintf( dqLog->logFile, message ) < 0 )
   {
      dqError_ExitWithMessageNoLog( STR_ERROR_LOG_FILE_WRITE );
   }
}

void dqLog_Error( const char* message )
{
   // don't bother check the result, we're probably already exiting
   fprintf( dqLog->logFile, "%s%s\n", STR_ERROR_MESSAGE_PREFIX, message );
}
