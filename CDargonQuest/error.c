#include "error.h"
#include "strings.h"

#include <stdio.h>
#include <stdlib.h>

void dqError_ExitWithMessage( const char* message )
{
   printf( "\n\n%s%s\n\n", STR_ERROR_MESSAGE_PREFIX, message );
   exit( 1 );
}
