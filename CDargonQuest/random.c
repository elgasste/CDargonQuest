#include "random.h"

void dqRandom_Init()
{
   srand( (unsigned int)time( 0 ) );
}

unsigned int dqRandom_Percent()
{
   // from 0 to 100 percent
   return (unsigned int)( rand() % 101 );
}

unsigned int dqRandom_UnsignedInt( unsigned int min, unsigned int max )
{
   // min and max inclusive
   return ( (unsigned int)rand() % ( ( max + 1 ) - min ) ) + min;
}
