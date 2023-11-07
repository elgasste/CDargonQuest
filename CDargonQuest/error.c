#include "error.h"
#include "strings.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>

void dqError_Message( const char* message )
{

   printf( "\n\n%s%s\n\n", STR_ERROR_MESSAGE_PREFIX, message );
}

void dqError_ExitWithMessage( const char* message )
{
   printf( "\n\n%s%s\n\n", STR_ERROR_MESSAGE_PREFIX, message );
   dqLog_Error( message );
   exit( 1 );
}

void dqError_ExitWithMessageNoLog( const char* message )
{
   printf( "\n\n%s%s\n\n", STR_ERROR_MESSAGE_PREFIX, message );
   exit( 1 );
}
