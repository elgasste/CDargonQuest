#include "render_config.h"

void dqRenderConfig_Init()
{
   int i;

   dqRenderConfig = (dqRenderConfig_t*)dqMalloc( sizeof( dqRenderConfig_t ), sfTrue );

   dqRenderConfig->minFrameRate = 30;
   dqRenderConfig->maxFrameRate = 120;

   dqRenderConfig->windowWidth = 1920;
   dqRenderConfig->windowHeight = 1280;
   dqRenderConfig->screenWidth = 480;
   dqRenderConfig->screenHeight = 320;
   dqRenderConfig->windowBPP = 32;
   dqRenderConfig->windowStyle = sfTitlebar | sfClose;
   dqRenderConfig->windowClearColor = sfColor_fromRGB( 32, 32, 32 );

   dqRenderConfig->showDiagnostics = sfFalse;
   dqRenderConfig->diagnosticsFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->diagnosticsFontSize = 30;
   dqRenderConfig->diagnosticsFontScale.x = 0.2f;
   dqRenderConfig->diagnosticsFontScale.y = 0.2f;
   dqRenderConfig->diagnosticsFontColor = sfWhite;
   dqRenderConfig->diagnosticsBackgroundColor = sfBlue;
   dqRenderConfig->diagnosticsWidth = 108;
   dqRenderConfig->diagnosticsHeight = 60;
   dqRenderConfig->diagnosticsPadding = 8;
   dqRenderConfig->diagnosticsLineWidth = 40;
   dqRenderConfig->diagnosticsRefreshRate = 0.25f;

   dqRenderConfig->dialogSpriteSize = 8;

   dqRenderConfig->overworldViewSize.x = 448;
   dqRenderConfig->overworldViewSize.y = 256;
   dqRenderConfig->overworldViewOffset.x = 16;
   dqRenderConfig->overworldViewOffset.y = 16;

   dqRenderConfig->battleStatsDialogPos.x = dqRenderConfig->overworldViewOffset.x + (float)( dqRenderConfig->dialogSpriteSize );
   dqRenderConfig->battleStatsDialogPos.y = dqRenderConfig->overworldViewOffset.y + (float)( dqRenderConfig->dialogSpriteSize );
   dqRenderConfig->battleStatsDialogWidth = 10;
   dqRenderConfig->battleStatsDialogHeight = 9;
   dqRenderConfig->battleMessageDialogPos.x = dqRenderConfig->overworldViewOffset.x + (float)( dqRenderConfig->dialogSpriteSize );
   dqRenderConfig->battleMessageDialogPos.y = dqRenderConfig->overworldViewSize.y - ( dqRenderConfig->dialogSpriteSize * 10 ) - dqRenderConfig->overworldViewOffset.y;
   dqRenderConfig->battleMessageDialogWidth = 54;
   dqRenderConfig->battleMessageDialogHeight = 13;
   dqRenderConfig->battleActionMenuDialogPos.x = dqRenderConfig->overworldViewOffset.x + (float)( dqRenderConfig->dialogSpriteSize );;
   dqRenderConfig->battleActionMenuDialogPos.y = dqRenderConfig->overworldViewSize.y - ( dqRenderConfig->dialogSpriteSize * 10 ) - dqRenderConfig->overworldViewOffset.y;
   dqRenderConfig->battleActionMenuDialogWidth = 10;
   dqRenderConfig->battleActionMenuDialogHeight = 13;

   dqRenderConfig->menuCaratText = ">";
   dqRenderConfig->menuCaratBlinkRate = 0.3f;

   dqRenderConfig->titleMenuOptionsPos.x = (float)( 28 * dqRenderConfig->dialogSpriteSize );
   dqRenderConfig->titleMenuOptionsPos.y = (float)( 19 * dqRenderConfig->dialogSpriteSize );
   dqRenderConfig->titleMenuOptionsWidth = 8;
   dqRenderConfig->titleMenuCaratOffsetX = -2;

   dqRenderConfig->battleActionMenuOptionsPos.x = dqRenderConfig->battleMessageDialogPos.x + ( dqRenderConfig->dialogSpriteSize * 2 );
   dqRenderConfig->battleActionMenuOptionsPos.y = dqRenderConfig->battleMessageDialogPos.y + ( dqRenderConfig->dialogSpriteSize * 2 );
   dqRenderConfig->battleActionMenuOptionsWidth = 6;
   dqRenderConfig->battleActionMenuCaratOffsetX = -1;

   dqRenderConfig->titleBackdropColor = sfBlack;
   dqRenderConfig->passableOverlayColor = sfColor_fromRGBA( 0, 255, 0, 128 );
   dqRenderConfig->impassableOverlayColor = sfColor_fromRGBA( 255, 0, 0, 128 );
   dqRenderConfig->mapSwapOverlayColor = sfColor_fromRGBA( 0, 0, 255, 128 );
   dqRenderConfig->battleBackdropColor = sfBlack;

   dqRenderConfig->overworldTilesetTexturePath = "Resources/Tilesets/overworld.png";
   dqRenderConfig->dialogTilesetTexturePath = "Resources/Tilesets/text.png";

   dqRenderConfig->overworldTileTextureColumns = 16;
   dqRenderConfig->overworldTileTextureRows = 3;

   dqRenderConfig->dialogTileTextureColumns = 10;
   dqRenderConfig->dialogTileTextureRows = 10;

   dqRenderConfig->dialogScrollCharSeconds = 0.01f;

   dqRenderConfig->enemyTextureSize0Path = "Resources/Sprites/enemy_size_0.png";
   dqRenderConfig->enemyTextureSize1Path = "Resources/Sprites/enemy_size_1.png";
   dqRenderConfig->enemyTextureSize2Path = "Resources/Sprites/enemy_size_2.png";
   dqRenderConfig->enemyTextureSize3Path = "Resources/Sprites/enemy_size_3.png";
   dqRenderConfig->playerTexturePath = "Resources/Sprites/player.png";

   dqRenderConfig->enemySpriteHeight = 64;
   dqRenderConfig->enemySpriteWidths[0] = 16;
   dqRenderConfig->enemySpriteWidths[1] = 24;
   dqRenderConfig->enemySpriteWidths[2] = 32;
   dqRenderConfig->enemySpriteWidths[3] = 40;
   dqRenderConfig->enemyAreaPosY = 96;

   dqRenderConfig->overworldFadeOutSeconds = 0.3f;
   dqRenderConfig->overworldStayFadedSeconds = 0.2f;
   dqRenderConfig->overworldFadeInSeconds = 0.3f;
   dqRenderConfig->cheatFontFilePath = "Resources/Fonts/Consolas.ttf";
   dqRenderConfig->cheatFontSize = 30;
   dqRenderConfig->cheatFontScale.x = 0.2f;
   dqRenderConfig->cheatFontScale.y = 0.2f;
   dqRenderConfig->cheatLetterSpacing = 0.1f;
   dqRenderConfig->cheatFontColor = sfWhite;

   for ( i = 0; i < 128; i++ )
   {
      if ( i >= 32 && i <= 122 )
      {
         dqRenderConfig->textMap[i] = i - 32;
      }
      else
      {
         dqRenderConfig->textMap[i] = 61; // space
      }
   }

   dqRenderConfig->dialogLeftBorderIndex = 92;
   dqRenderConfig->dialogTopBorderIndex = 93;
   dqRenderConfig->dialogRightBorderIndex = 94;
   dqRenderConfig->dialogBottomBorderIndex = 95;
   dqRenderConfig->dialogTopLeftBorderIndex = 96;
   dqRenderConfig->dialogTopRightBorderIndex = 97;
   dqRenderConfig->dialogBottomRightBorderIndex = 98;
   dqRenderConfig->dialogBottomLeftBorderIndex = 99;
}

void dqRenderConfig_Cleanup()
{
   dqFree( dqRenderConfig, sizeof( dqRenderConfig_t ), sfTrue );
}
