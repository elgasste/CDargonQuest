#include "render_config.h"

void dqRenderConfig_Init()
{
   int i;

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

   dqRenderConfig->overworldTilesetTexturePath = "Resources/Tilesets/overworld.png";
   dqRenderConfig->dialogTilesetTexturePath = "Resources/Tilesets/text.png";

   dqRenderConfig->dialogSpriteSize = 8;

   dqRenderConfig->overworldTileTextureColumns = 16;
   dqRenderConfig->overworldTileTextureRows = 3;

   dqRenderConfig->dialogTileTextureColumns = 9;
   dqRenderConfig->dialogTileTextureRows = 8;

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

   dqRenderConfig->battleMessageDialogPos.x = dqRenderConfig->overworldViewOffset.x;
   dqRenderConfig->battleMessageDialogPos.y = dqRenderConfig->overworldViewSize.y - ( dqRenderConfig->dialogSpriteSize * 8 ) - dqRenderConfig->overworldViewOffset.y;
   dqRenderConfig->battleMessageDialogWidth = 28 * 2; // dialog sprites are 8 pixels, overworld sprites are 16 pixels
   dqRenderConfig->battleMessageDialogHeight = 6 * 2;

   for ( i = 0; i < 128; i++ )
   {
      if ( i >= 65 && i <= 90 )
      {
         // 65-90 are upper-case letters, starting at tile index 9
         dqRenderConfig->textMap[i] = i - 56;
      }
      else if ( i >= 97 && i <= 122 )
      {
         // 97-122 are lower-case letters, starting at tile index 35
         dqRenderConfig->textMap[i] = i - 62;
      }
      else
      {
         switch ( i )
         {
            case 32: dqRenderConfig->textMap[i] = 61; break; // space
            case 33: dqRenderConfig->textMap[i] = 62; break; // exclamation point
            case 34: dqRenderConfig->textMap[i] = 63; break; // double-quote
            case 39: dqRenderConfig->textMap[i] = 64; break; // single-quote
            case 40: dqRenderConfig->textMap[i] = 66; break; // left parenthesis
            case 41: dqRenderConfig->textMap[i] = 67; break; // right parenthesis
            case 42: dqRenderConfig->textMap[i] = 71; break; // star
            case 44: dqRenderConfig->textMap[i] = 69; break; // comma
            case 45: dqRenderConfig->textMap[i] = 68; break; // dash
            case 46: dqRenderConfig->textMap[i] = 70; break; // period
            case 63: dqRenderConfig->textMap[i] = 65; break; // question mark
            default: dqRenderConfig->textMap[i] = 61; break; // space
         }
      }
   }

   dqRenderConfig->dialogTopLeftBorderIndex = 4;
   dqRenderConfig->dialogTopRightBorderIndex = 5;
   dqRenderConfig->dialogBottomLeftBorderIndex = 7;
   dqRenderConfig->dialogBottomRightBorderIndex = 6;
   dqRenderConfig->dialogLeftBorderIndex = 0;
   dqRenderConfig->dialogTopBorderIndex = 1;
   dqRenderConfig->dialogRightBorderIndex = 2;
   dqRenderConfig->dialogBottomBorderIndex = 3;
}

void dqRenderConfig_Cleanup()
{
   dqFree( dqRenderConfig );
}
