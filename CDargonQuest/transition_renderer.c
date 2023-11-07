#include "transition_renderer.h"
#include "render_config.h"
#include "clock.h"
#include "window.h"
#include "event_queue.h"

void dqTransitionRenderer_Init()
{
   dqTransitionRenderer = (dqTransitionRenderer_t*)malloc( sizeof( dqTransitionRenderer_t ) );
   CHECK_MALLOC( dqTransitionRenderer )

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
   float fadePercentage, fadeInSeconds, sec;

   dqTransitionRenderer->elapsedSeconds += dqClock->lastFrameSeconds;
   sec = dqTransitionRenderer->elapsedSeconds;

   if ( sec < dqRenderConfig->overworldFadeOutSeconds )
   {
      // fading out
      fadePercentage = sec / dqRenderConfig->overworldFadeOutSeconds;
      sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, (sfUint8)( fadePercentage * 255 ) ) );
   }
   else if ( sec < ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldStayFadedSeconds ) )
   {
      // faded out, waiting to fade in
      if ( !dqTransitionRenderer->raisedFadedOut )
      {
         dqEventQueue_Push( dqEventOverworldFadedOut, 0 );
         dqTransitionRenderer->raisedFadedOut = sfTrue;
      }

      sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfBlack );
   }
   else if ( sec < ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldStayFadedSeconds + dqRenderConfig->overworldFadeInSeconds ) )
   {
      // fading in
      fadeInSeconds = sec - ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldStayFadedSeconds );
      fadePercentage = 1.0f - ( fadeInSeconds / dqRenderConfig->overworldFadeInSeconds );
      sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, (sfUint8)( fadePercentage * 255 ) ) );
   }
   else
   {
      // done fading
      if ( !dqTransitionRenderer->raisedFadedIn )
      {
         dqEventQueue_Push( dqEventOverworldFadedIn, 0 );
         dqTransitionRenderer->raisedFadedIn = sfTrue;
      }

      sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, 0 ) );
   }

   dqWindow_DrawRectangleShape( dqTransitionRenderer->fadeRect );
}
