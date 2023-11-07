#include "entity_sprite.h"
#include "clock.h"
#include "window.h"

dqEntitySprite_t* dqEntitySprite_Create( dqEntity_t* entity,
                                         sfTexture* texture,
                                         int width,
                                         int height,
                                         unsigned int frameCount,
                                         float frameTimeThreshold )
{
   dqEntitySprite_t* sprite = (dqEntitySprite_t*)malloc( sizeof( dqEntitySprite_t ) );
   CHECK_MALLOC( sprite )

   sprite->entity = entity;

   sprite->sprite = sfSprite_create();

   sfSprite_setTexture( sprite->sprite, texture, sfFalse );
   sprite->textureRect.width = width;
   sprite->textureRect.height = height;

   sprite->hitBoxOffset.x = ( sprite->textureRect.width - entity->hitBoxSize.x ) / 2;
   sprite->hitBoxOffset.y = ( sprite->textureRect.height - entity->hitBoxSize.y ) / 2;

   sprite->currentFrame = 0;
   sprite->frameCount = frameCount;

   sprite->elapsedFrameSeconds = 0;
   sprite->frameTimeThreshold = frameTimeThreshold;

   return sprite;
}

void dqEntitySprite_Cleanup( dqEntitySprite_t* sprite )
{
   sfSprite_destroy( sprite->sprite );

   SAFE_DELETE( sprite )
}

void dqEntitySprite_Tick( dqEntitySprite_t* sprite )
{
   if ( sprite->entity->velocityX != 0 || sprite->entity->velocityY != 0 )
   {
      sprite->elapsedFrameSeconds += dqClock->lastFrameSeconds;
   }

   while ( sprite->elapsedFrameSeconds >= sprite->frameTimeThreshold )
   {
      sprite->elapsedFrameSeconds -= sprite->frameTimeThreshold;
      sprite->currentFrame++;

      if ( sprite->currentFrame >= sprite->frameCount )
      {
         sprite->currentFrame = 0;
      }
   }

   sprite->textureRect.left = sprite->currentFrame * sprite->textureRect.width;
   sprite->textureRect.top = (int)sprite->entity->direction * sprite->textureRect.height;
   sfSprite_setTextureRect( sprite->sprite, sprite->textureRect );
}
