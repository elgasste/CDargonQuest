#pragma once

#include "common.h"
#include "direction.h"

typedef struct
{
   sfVector2f hitBoxPosition;
   sfVector2f hitBoxSize;
   sfVector2f centerPosition;

   float velocityX;
   float velocityY;

   dqDirection direction;
}
dqEntity_t;
