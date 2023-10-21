#include <stdio.h>

#include "game.h"

int main()
{
   printf( STR_LOADING_THINGS );
   dqGame_Init();
   printf( "%s\n%s", STR_DONE, STR_HAVE_FUN );
   dqGame_Run();
   printf( "\n%s", STR_CLEANING_UP );
   dqGame_Cleanup();
   printf( "%s\n\n%s\n\n", STR_DONE, STR_BURRITO );

   return 0;
}
