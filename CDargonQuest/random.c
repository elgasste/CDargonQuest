#include "random.h"

void dqRandom_Init()
{
   srand( (unsigned int)time( NULL ) );
}

unsigned int dqRandom_Percent()
{
   return (unsigned int)( rand() % 99 );
}
