#include "render_config.h"

void dqRenderConfig_Init()
{
   dqRenderConfig = (dqRenderConfig_t*)malloc( sizeof( dqRenderConfig_t ) );

#pragma warning ( suppress:6011 )
   dqRenderConfig->minFrameRate = 20;
   dqRenderConfig->maxFrameRate = 60;

   dqRenderConfig->windowWidth = 1920;
   dqRenderConfig->windowHeight = 1280;
   dqRenderConfig->windowBPP = 32;
   dqRenderConfig->windowStyle = sfTitlebar | sfClose;
   dqRenderConfig->windowClearColor = sfBlack;

   dqRenderConfig->showDiagnostics = sfFalse;
   dqRenderConfig->diagnosticsFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->diagnosticsFontSize = 24;
   dqRenderConfig->diagnosticsFontColor = sfWhite;
   dqRenderConfig->diagnosticsBackgroundColor = sfBlue;
   dqRenderConfig->diagnosticsWidth = 400;
   dqRenderConfig->diagnosticsHeight = 208;
   dqRenderConfig->diagnosticsPadding = 18;
   dqRenderConfig->diagnosticsLineWidth = 40;
   dqRenderConfig->diagnosticsRefreshRate = 0.25f;

   dqRenderConfig->menuFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->menuFontSize = 50;
   dqRenderConfig->menuFontColor = sfWhite;
   dqRenderConfig->menuCaratText = ">";
   dqRenderConfig->menuCaratOffsetX = -50;
   dqRenderConfig->menuCaratBlinkRate = 0.3f;

   dqRenderConfig->titleMenuOffsetX = 900;
   dqRenderConfig->titleMenuOffsetY = 600;

   dqRenderConfig->tileSize = 16;
}

void dqRenderConfig_Cleanup()
{
   SAFE_DELETE( dqRenderConfig )
}
