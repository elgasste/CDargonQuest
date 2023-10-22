#include "diagnostics_renderer.h"
#include "render_config.h"
#include "window.h"
#include "clock.h"

void dqDiagnosticsRenderer_Init()
{
   sfVector2f backgroundSize = { dqRenderConfig->diagnosticsWidth, dqRenderConfig->diagnosticsHeight };
   sfVector2f backgroundPosition = { dqRenderConfig->windowWidth - dqRenderConfig->diagnosticsWidth, 0 };

   dqDiagnosticsRenderer = (dqDiagnosticsRenderer_t*)malloc( sizeof( dqDiagnosticsRenderer_t ) );

#pragma warning ( suppress:6011 )
   dqDiagnosticsRenderer->textLine = (char*)calloc( sizeof( char ), dqRenderConfig->diagnosticsLineWidth );

   dqDiagnosticsRenderer->background = sfRectangleShape_create();
   sfRectangleShape_setSize( dqDiagnosticsRenderer->background, backgroundSize );
   sfRectangleShape_setPosition( dqDiagnosticsRenderer->background, backgroundPosition );
   sfRectangleShape_setFillColor( dqDiagnosticsRenderer->background, dqRenderConfig->diagnosticsBackgroundColor );

   dqDiagnosticsRenderer->font = sfFont_createFromFile( dqRenderConfig->diagnosticsFontFilePath );

   dqDiagnosticsRenderer->textPosition.x = dqRenderConfig->windowWidth - dqRenderConfig->diagnosticsWidth + dqRenderConfig->diagnosticsPadding;

   dqDiagnosticsRenderer->text = sfText_create();
   sfText_setFont( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->font );
   sfText_setCharacterSize( dqDiagnosticsRenderer->text, dqRenderConfig->diagnosticsFontSize );
   sfText_setFillColor( dqDiagnosticsRenderer->text, dqRenderConfig->diagnosticsFontColor );

   dqDiagnosticsRenderer->lineSpacing = sfFont_getLineSpacing( dqDiagnosticsRenderer->font,
                                                               sfText_getCharacterSize( dqDiagnosticsRenderer->text ) );
}

void dqDiagnosticsRenderer_Cleanup()
{
   sfText_destroy( dqDiagnosticsRenderer->text );
   sfFont_destroy( dqDiagnosticsRenderer->font );

   SAFE_DELETE( dqDiagnosticsRenderer );
}

void dqDiagnosticsRenderer_Render()
{
   sfRenderWindow_drawRectangleShape( dqWindow, dqDiagnosticsRenderer->background, NULL );

   dqDiagnosticsRenderer->textPosition.y = dqRenderConfig->diagnosticsPadding;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_MAX_FRAME_RATE,
              dqRenderConfig->maxFrameRate );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   sfRenderWindow_drawText( dqWindow, dqDiagnosticsRenderer->text, NULL );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_MIN_FRAME_RATE,
              dqRenderConfig->minFrameRate );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   sfRenderWindow_drawText( dqWindow, dqDiagnosticsRenderer->text, NULL );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_CUR_FRAME_RATE,
              dqClock_CurrentFrameRate() );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   sfRenderWindow_drawText( dqWindow, dqDiagnosticsRenderer->text, NULL );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_AVG_FRAME_RATE,
              dqClock_AverageFrameRate() );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   sfRenderWindow_drawText( dqWindow, dqDiagnosticsRenderer->text, NULL );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_TOTAL_FRAMES,
              dqClock->frameCount );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   sfRenderWindow_drawText( dqWindow, dqDiagnosticsRenderer->text, NULL );

   dqDiagnosticsRenderer->textPosition.y += dqDiagnosticsRenderer->lineSpacing;
   sfText_setPosition( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textPosition );
   sprintf_s( dqDiagnosticsRenderer->textLine,
              dqRenderConfig->diagnosticsLineWidth,
              "%s%d",
              STR_DIAGNOSTICS_LAG_FRAMES,
              dqClock->lagFrameCount );
   sfText_setString( dqDiagnosticsRenderer->text, dqDiagnosticsRenderer->textLine );
   sfRenderWindow_drawText( dqWindow, dqDiagnosticsRenderer->text, NULL );
}
