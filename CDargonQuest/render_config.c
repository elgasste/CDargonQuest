#include "render_config.h"

void dqRenderConfig_Init()
{
   dqRenderConfig = (dqRenderConfig_t*)malloc( sizeof( dqRenderConfig_t ) );

#pragma warning ( suppress:6011 )
   dqRenderConfig->minFrameRate = 20;
   dqRenderConfig->maxFrameRate = 60;

   dqRenderConfig->windowWidth = 1920;
   dqRenderConfig->windowHeight = 1280;
   dqRenderConfig->screenWidth = 480;
   dqRenderConfig->screenHeight = 320;
   dqRenderConfig->windowBPP = 32;
   dqRenderConfig->windowStyle = sfTitlebar | sfClose;
   dqRenderConfig->windowClearColor = sfBlack;

   dqRenderConfig->showDiagnostics = sfFalse;
   dqRenderConfig->diagnosticsFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->diagnosticsFontSize = 10;
   dqRenderConfig->diagnosticsFontColor = sfWhite;
   dqRenderConfig->diagnosticsBackgroundColor = sfBlue;
   dqRenderConfig->diagnosticsWidth = 180;
   dqRenderConfig->diagnosticsHeight = 96;
   dqRenderConfig->diagnosticsPadding = 10;
   dqRenderConfig->diagnosticsLineWidth = 40;
   dqRenderConfig->diagnosticsRefreshRate = 0.25f;

   dqRenderConfig->menuFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->menuFontSize = 14;
   dqRenderConfig->menuFontColor = sfWhite;
   dqRenderConfig->menuCaratText = ">";
   dqRenderConfig->menuCaratOffsetX = -14;
   dqRenderConfig->menuCaratBlinkRate = 0.3f;

   dqRenderConfig->titleMenuOffsetX = 225;
   dqRenderConfig->titleMenuOffsetY = 150;

   dqRenderConfig->tileSize = 16;

   dqRenderConfig->playerTexturePath = "Resources/Sprites/player.png";
}

void dqRenderConfig_Cleanup()
{
   SAFE_DELETE( dqRenderConfig )
}
