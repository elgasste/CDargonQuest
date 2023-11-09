#include "common.h"

void* dqMalloc( size_t size )
{
   void* mem = malloc( size );

   if ( !mem )
   {
      dqError_Message( STR_ERROR_MALLOC );
      exit( 1 );
   }

   return mem;
}

void dqFree( void* mem )
{
   if ( mem )
   {
      free( mem );
      mem = NULL;
   }
}
