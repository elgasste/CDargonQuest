#include "transition_renderer.h"
#include "render_config.h"
#include "clock.h"
#include "window.h"
#include "event_queue.h"

void dqTransitionRenderer_Init()
{
   dqTransitionRenderer = (dqTransitionRenderer_t*)dqMalloc( sizeof( dqTransitionRenderer_t ), sfTrue );

   dqTransitionRenderer->fadeRect = dqRectangleShape_Create();
   sfRectangleShape_setSize( dqTransitionRenderer->fadeRect, dqRenderConfig->overworldViewSize );
   sfRectangleShape_setPosition( dqTransitionRenderer->fadeRect, dqRenderConfig->overworldViewOffset );

   dqTransitionRenderer_Reset();
}

void dqTransitionRenderer_Cleanup()
{
   dqRectangleShape_Destroy( dqTransitionRenderer->fadeRect );

   dqFree( dqTransitionRenderer, sizeof( dqTransitionRenderer_t ), sfTrue );
}

void dqTransitionRenderer_Reset()
{
   sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, 0 ) );

   dqTransitionRenderer->elapsedSeconds = 0;
   dqTransitionRenderer->fadingIn = sfFalse;
   dqTransitionRenderer->fadingOut = sfTrue;
   dqTransitionRenderer->raisedFadedOut = sfFalse;
   dqTransitionRenderer->raisedFadedIn = sfFalse;
}

// TODO: I suppose it's possible for the frame rate to drop so low that we completely skip over
// one of the conditions in here, that should probably be addressed.
void dqTransitionRenderer_Render( sfBool black )
{
   float fadePercentage, fadeInSeconds, sec;

   dqTransitionRenderer->elapsedSeconds += dqClock->lastFrameSeconds;
   sec = dqTransitionRenderer->elapsedSeconds;

   if ( sec < dqRenderConfig->overworldFadeOutSeconds )
   {
      dqTransitionRenderer->fadingIn = sfFalse;
      dqTransitionRenderer->fadingOut = sfTrue;
      fadePercentage = sec / dqRenderConfig->overworldFadeOutSeconds;

      if ( black )
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, (sfUint8)( fadePercentage * 255 ) ) );
      }
      else
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 255, 255, 255, (sfUint8)( fadePercentage * 255 ) ) );
      }
   }
   else if ( sec < ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldStayFadedSeconds ) )
   {
      dqTransitionRenderer->fadingIn = sfFalse;
      dqTransitionRenderer->fadingOut = sfFalse;

      if ( !dqTransitionRenderer->raisedFadedOut )
      {
         dqEventQueue_Push( dqEventFadedOut, 0 );
         dqTransitionRenderer->raisedFadedOut = sfTrue;
      }

      if ( black )
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfBlack );
      }
      else
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfWhite );
      }
   }
   else if ( sec < ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldStayFadedSeconds + dqRenderConfig->overworldFadeInSeconds ) )
   {
      dqTransitionRenderer->fadingIn = sfTrue;
      dqTransitionRenderer->fadingOut = sfFalse;
      fadeInSeconds = sec - ( dqRenderConfig->overworldFadeOutSeconds + dqRenderConfig->overworldStayFadedSeconds );
      fadePercentage = 1.0f - ( fadeInSeconds / dqRenderConfig->overworldFadeInSeconds );

      if ( black )
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, (sfUint8)( fadePercentage * 255 ) ) );
      }
      else
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 255, 255, 255, (sfUint8)( fadePercentage * 255 ) ) );
      }
   }
   else
   {
      dqTransitionRenderer->fadingIn = sfFalse;
      dqTransitionRenderer->fadingOut = sfFalse;

      if ( !dqTransitionRenderer->raisedFadedIn )
      {
         dqEventQueue_Push( dqEventFadedIn, 0 );
         dqTransitionRenderer->raisedFadedIn = sfTrue;
      }

      if ( black )
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 0, 0, 0, 0 ) );
      }
      else
      {
         sfRectangleShape_setFillColor( dqTransitionRenderer->fadeRect, sfColor_fromRGBA( 255, 255, 255, 0 ) );
      }
   }

   dqWindow_DrawRectangleShape( dqTransitionRenderer->fadeRect );
}
