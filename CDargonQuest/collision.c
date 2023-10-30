#include "collision.h"
#include "entity.h"
#include "clock.h"
#include "game_data.h"
#include "map.h"

void dqCollision_ClipEntity( dqEntity_t* entity );

void dqCollision_MoveEntity( dqEntity_t* entity )
{
   if ( entity->velocityX != 0 )
   {
      entity->centerPosition.x += ( entity->velocityX * dqClock->lastFrameSeconds );
      entity->hitBoxPosition.x += ( entity->velocityX * dqClock->lastFrameSeconds );
   }

   if ( entity->velocityY != 0 )
   {
      entity->centerPosition.y += ( entity->velocityY * dqClock->lastFrameSeconds );
      entity->hitBoxPosition.y += ( entity->velocityY * dqClock->lastFrameSeconds );
   }

   dqCollision_ClipEntity( entity );
}

void dqCollision_ClipEntity( dqEntity_t* entity )
{
   if ( entity->hitBoxPosition.x < 0 )
   {
      entity->hitBoxPosition.x = 0;
      entity->centerPosition.x = entity->hitBoxSize.x / 2;
   }
   else if ( entity->hitBoxPosition.x + entity->hitBoxSize.x >= dqGameData->maps[0].size.x )
   {
      entity->hitBoxPosition.x = dqGameData->maps[0].size.x - entity->hitBoxSize.x;
      entity->centerPosition.x = entity->hitBoxPosition.x + ( entity->hitBoxSize.x / 2 );
   }

   if ( entity->hitBoxPosition.y < 0 )
   {
      entity->hitBoxPosition.y = 0;
      entity->centerPosition.y = entity->hitBoxSize.y / 2;
   }
   else if ( entity->hitBoxPosition.y + entity->hitBoxSize.y >= dqGameData->maps[0].size.y )
   {
      entity->hitBoxPosition.y = dqGameData->maps[0].size.y - entity->hitBoxSize.y;
      entity->centerPosition.y = entity->hitBoxPosition.y + ( entity->hitBoxSize.y / 2 );
   }
}
