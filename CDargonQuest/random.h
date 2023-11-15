#if !defined( DQ_RANDOM_H )
#define DQ_RANDOM_H

#include "common.h"

void dqRandom_Init();
unsigned int dqRandom_Percent();
unsigned int dqRandom_UnsignedInt( unsigned int min, unsigned int max );

#endif
