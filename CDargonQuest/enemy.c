#include "enemy.h"
#include "battle_stats.h"

void dqEnemy_Cleanup( dqEnemy_t* enemy )
{
   dqFree( enemy, sizeof( dqEnemy_t ), sfTrue );
}
