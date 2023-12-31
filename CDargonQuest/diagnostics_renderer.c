#include "diagnostics_renderer.h"
#include "render_config.h"
#include "window.h"
#include "clock.h"

void dqDiagnosticsRenderer_Init()
{
   sfVector2f backgroundSize = { dqRenderConfig->diagnosticsWidth, dqRenderConfig->diagnosticsHeight };
   sfVector2f backgroundPosition = { dqRenderConfig->screenWidth - dqRenderConfig->diagnosticsWidth, 0 };

   dqDiagnosticsRenderer = (dqDiagnosticsRenderer_t*)dqMalloc( sizeof( dqDiagnosticsRenderer_t ), sfTrue );

   dqDiagnosticsRenderer->textLine = (char*)dqCalloc( dqRenderConfig->diagnosticsLineWidth, sizeof( char ), sfTrue );

   dqDiagnosticsRenderer->background = dqRectangleShape_Create();
   sfRectangleShape_setSize( dqDiagnosticsRenderer->background, backgroundSize );
   sfRectangleShape_setPosition( dqDiagnosticsRenderer->background, backgroundPosition );
   sfRectangleShape_setFillColor( dqDiagnosticsRenderer->background, dqRenderConfig->diagnosticsBackgroundColor );

   dqDiagnosticsRenderer->font = dqFont_CreateFromFile( dqRenderConfig->diagnosticsFontFilePath );

   dqDiagnosticsRenderer->textPosition.x = dqRenderConfig->screenWidth - dqRenderConfig->diagnosticsWidth + dqRenderConfig->diagnosticsPadding;

   dqDiagnosticsRenderer->text = dqText_Create();
   sfText_setFont( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->font );
   sfText_setCharacterSize( dqDiagnosticsRenderer->text, dqRenderConfig->diagnosticsFontSize );
   sfText_setScale( dqDiagnosticsRenderer->text, dqRenderConfig->diagnosticsFontScale );
   sfText_setFillColor( dqDiagnosticsRenderer->text, dqRenderConfig->diagnosticsFontColor );

   dqDiagnosticsRenderer->lineSpacing = sfFont_getLineSpacing( dqDiagnosticsRenderer->font,
                                                               sfText_getCharacterSize( dqDiagnosticsRenderer->text ) ) * dqRenderConfig->diagnosticsFontScale.x;

   dqDiagnosticsRenderer->currentFrameRateCache = 0;
   dqDiagnosticsRenderer->averageFrameRateCache = 0;
   dqDiagnosticsRenderer->refreshElapsedSeconds = 0;
}

void dqDiagnosticsRenderer_Cleanup()
{
   dqText_Destroy( dqDiagnosticsRenderer->text );
   dqFont_Destroy( dqDiagnosticsRenderer->font );
   dqRectangleShape_Destroy( dqDiagnosticsRenderer->background );

   dqFree( dqDiagnosticsRenderer->textLine, sizeof( char ) * dqRenderConfig->diagnosticsLineWidth, sfTrue );
   dqFree( dqDiagnosticsRenderer, sizeof( dqDiagnosticsRenderer_t ), sfTrue );
}

void dqDiagnosticsRenderer_Render()
{
   dqDiagnosticsRenderer->refreshElapsedSeconds += dqClock->lastFrameSeconds;

   if ( dqDiagnosticsRenderer->refreshElapsedSeconds >= dqRenderConfig->diagnosticsRefreshRate )
   {
      dqDiagnosticsRenderer->currentFrameRateCache = dqClock->currentFrameRate;
      dqDiagnosticsRenderer->averageFrameRateCache = dqClock->averageFrameRate;
      dqDiagnosticsRenderer->refreshElapsedSeconds = 0;
   }

   dqWindow_DrawRectangleShape( dqDiagnosticsRenderer->background );

   dqDiagnosticsRenderer->textPosition.y = dqRenderConfig->diagnosticsPadding;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_MAX_FRAME_RATE,
              dqRenderConfig->maxFrameRate );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   dqWindow_DrawText( dqDiagnosticsRenderer->text );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_MIN_FRAME_RATE,
              dqRenderConfig->minFrameRate );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   dqWindow_DrawText( dqDiagnosticsRenderer->text );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_CUR_FRAME_RATE,
              dqDiagnosticsRenderer->currentFrameRateCache );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   dqWindow_DrawText( dqDiagnosticsRenderer->text );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_AVG_FRAME_RATE,
              dqDiagnosticsRenderer->averageFrameRateCache );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   dqWindow_DrawText( dqDiagnosticsRenderer->text );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_TOTAL_FRAMES,
              dqClock->frameCount );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   dqWindow_DrawText( dqDiagnosticsRenderer->text );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_LAG_FRAMES,
              dqClock->lagFrameCount );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   dqWindow_DrawText( dqDiagnosticsRenderer->text );
}
