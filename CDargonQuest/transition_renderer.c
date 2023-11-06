#include "transition_renderer.h"
#include "render_config.h"

void dqTransitionRenderer_Init()
{
   dqTransitionRenderer = (dqTransitionRenderer_t*)malloc( sizeof( dqTransitionRenderer_t ) );
   CHECK_MALLOC( dqTransitionRenderer )

   dqTransitionRenderer->fadeOutSeconds = dqRenderConfig->overworldFadeOutSeconds;
   dqTransitionRenderer->fadeInSeconds = dqRenderConfig->overworldFadeInSeconds;

   dqTransitionRenderer_Reset();
}

void dqTransitionRenderer_Cleanup()
{
   SAFE_DELETE( dqTransitionRenderer );
}

void dqTransitionRenderer_Reset()
{
   dqTransitionRenderer->elapsedSeconds = 0;
}

void dqTransitionRenderer_Render()
{
   // TODO: fade out, then raise a faded-out event
}
