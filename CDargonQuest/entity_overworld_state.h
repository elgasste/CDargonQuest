#if !defined( DQ_ENTITY_OVERWORLD_STATE_H )
#define DQ_ENTITY_OVERWORLD_STATE_H

#include "common.h"
#include "direction.h"

typedef struct dqEntityOverworldState_t
{
   sfVector2f hitBoxPosition;
   sfVector2f hitBoxSize;
   sfVector2f centerPosition;

   float velocityX;
   float velocityY;

   dqDirection direction;
}
dqEntityOverworldState_t;

#endif
