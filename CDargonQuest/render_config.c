#include "render_config.h"

void dqRenderConfig_Init()
{
   dqRenderConfig = (dqRenderConfig_t*)dqMalloc( sizeof( dqRenderConfig_t ) );

   dqRenderConfig->minFrameRate = 30;
   dqRenderConfig->maxFrameRate = 120;

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

   dqRenderConfig->overworldViewSize.x = 448;
   dqRenderConfig->overworldViewSize.y = 256;
   dqRenderConfig->overworldViewOffset.x = 16;
   dqRenderConfig->overworldViewOffset.y = 16;

   dqRenderConfig->passableOverlayColor = sfColor_fromRGBA( 0, 255, 0, 128 );
   dqRenderConfig->impassableOverlayColor = sfColor_fromRGBA( 255, 0, 0, 128 );
   dqRenderConfig->mapSwapOverlayColor = sfColor_fromRGBA( 0, 0, 255, 128 );

   dqRenderConfig->overworldTileTexturePath = "Resources/Tilesets/overworld.png";
   dqRenderConfig->overworldTileTextureColumns = 16;
   dqRenderConfig->overworldTileTextureRows = 3;

   dqRenderConfig->playerTexturePath = "Resources/Sprites/player.png";

   dqRenderConfig->overworldFadeOutSeconds = 0.3f;
   dqRenderConfig->overworldStayFadedSeconds = 0.2f;
   dqRenderConfig->overworldFadeInSeconds = 0.3f;
   dqRenderConfig->cheatFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->cheatFontSize = 30;
   dqRenderConfig->cheatFontScale.x = 0.2f;
   dqRenderConfig->cheatFontScale.y = 0.2f;
   dqRenderConfig->cheatLetterSpacing = 0.1f;
   dqRenderConfig->cheatFontColor = sfWhite;
}

void dqRenderConfig_Cleanup()
{
   dqFree( dqRenderConfig );
}
