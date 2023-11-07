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
   time_t t = time( NULL );
   struct tm tm;
   if ( localtime_s( &tm, &t ) )
   {
      dqError_ExitWithMessageNoLog( STR_ERROR_LOG_TIME );
   }

   if ( fprintf( dqLog->logFile, "%d-%02d-%02d %02d:%02d:%02d - %s\n",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                 tm.tm_hour, tm.tm_min, tm.tm_sec,
                 message ) < 0 )
   {
      dqError_ExitWithMessageNoLog( STR_ERROR_LOG_FILE_WRITE );
   }
}

void dqLog_Error( const char* message )
{
   // don't bother check the result, we're probably already exiting
   fprintf( dqLog->logFile, "%s%s\n", STR_ERROR_MESSAGE_PREFIX, message );
}
