#include "transition_renderer.h"
#include "render_config.h"
#include "clock.h"
#include "window.h"
#include "event_queue.h"

void dqTransitionRenderer_Init()
{
   dqTransitionRenderer = (dqTransitionRenderer_t*)malloc( sizeof( dqTransitionRenderer_t ) );
   CHECK_MALLOC( dqTransitionRenderer )

   dqTransitionRenderer->fadeOutSeconds = dqRenderConfig->overworldFadeOutSeconds;
   dqTransitionRenderer->fadeInSeconds = dqRenderConfig->overworldFadeInSeconds;

   dqTransitionRenderer->fadeRect = sfRectangleShape_create();
   sfRectangleShape_setSize( dqTransitionRenderer->fadeRect, dqRenderConfig->overworldViewSize );
   sfRectangleShape_setPosition( dqTransitionRenderer->fadeRect, dqRenderConfig->overworldViewOffset );

   dqTransitionRenderer_Reset();
}

void dqTransitionRenderer_Cleanup()
{
   sfRectangleShape_destroy( dqTransitionRenderer->fadeRect );

   SAFE_DELETE( dqTransitionRenderer );
}

void dqTransitionRenderer_Reset()
{
   sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, 0 ) );
   dqTransitionRenderer->elapsedSeconds = 0;

   dqTransitionRenderer->raisedFadedOut = sfFalse;
   dqTransitionRenderer->raisedFadedIn = sfFalse;
}

void dqTransitionRenderer_Render()
{
   float fadePercentage;
   float sec;

   dqTransitionRenderer->elapsedSeconds += dqClock->lastFrameSeconds;
   sec = dqTransitionRenderer->elapsedSeconds;

   if ( sec >= ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldFadeInSeconds ) )
   {
      if ( !dqTransitionRenderer->raisedFadedIn )
      {
         dqEventQueue_Push( dqEventOverworldFadedIn, 0 );
      }
   }
   else if ( sec >= dqRenderConfig->overworldFadeOutSeconds )
   {
      if ( !dqTransitionRenderer->raisedFadedOut )
      {
         dqEventQueue_Push( dqEventOverworldFadedOut, 0 );
         dqTransitionRenderer->raisedFadedOut = sfTrue;
      }

      fadePercentage = 1.0f - ( sec / dqRenderConfig->overworldFadeInSeconds );
      sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, (sfUint8)( fadePercentage * 255 ) ) );
   }
   else
   {
      fadePercentage = sec / dqRenderConfig->overworldFadeOutSeconds;
      sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, (sfUint8)( fadePercentage * 255 ) ) );
   }

   dqWindow_DrawRectangleShape( dqTransitionRenderer->fadeRect );
}
