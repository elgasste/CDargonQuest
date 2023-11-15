#if !defined( DQ_RENDER_CONFIG_H )
#define DQ_RENDER_CONFIG_H

#include "common.h"

typedef struct dqRenderConfig_t
{
   int minFrameRate;
   int maxFrameRate;

   unsigned int windowWidth;
   unsigned int windowHeight;
   float screenWidth;
   float screenHeight;
   unsigned int windowBPP;
   sfUint32 windowStyle;
   sfColor windowClearColor;

   sfBool showDiagnostics;
   const char* diagnosticsFontFilePath;
   unsigned int diagnosticsFontSize;
   sfVector2f diagnosticsFontScale;
   sfColor diagnosticsFontColor;
   sfColor diagnosticsBackgroundColor;
   float diagnosticsWidth;
   float diagnosticsHeight;
   float diagnosticsPadding;
   unsigned int diagnosticsLineWidth;
   float diagnosticsRefreshRate;

   unsigned int dialogSpriteSize;

   const char* menuCaratText;
   float menuCaratBlinkRate;

   sfVector2f titleMenuOptionsPos;
   unsigned int titleMenuOptionsWidth;
   int titleMenuCaratOffsetX;

   sfVector2f battleActionMenuOptionsPos;
   unsigned int battleActionMenuOptionsWidth;
   int battleActionMenuCaratOffsetX;

   sfVector2f overworldViewSize;
   sfVector2f overworldViewOffset;

   sfColor passableOverlayColor;
   sfColor impassableOverlayColor;
   sfColor mapSwapOverlayColor;

   const char* overworldTilesetTexturePath;
   const char* dialogTilesetTexturePath;

   unsigned int overworldTileTextureColumns;
   unsigned int overworldTileTextureRows;

   unsigned int dialogTileTextureColumns;
   unsigned int dialogTileTextureRows;

   float dialogScrollCharSeconds;

   const char* playerTexturePath;

   float overworldFadeOutSeconds;
   float overworldStayFadedSeconds;
   float overworldFadeInSeconds;

   const char* cheatFontFilePath;
   unsigned int cheatFontSize;
   sfVector2f cheatFontScale;
   float cheatLetterSpacing;
   sfColor cheatFontColor;

   sfVector2f battleMessageDialogPos;
   unsigned int battleMessageDialogWidth;
   unsigned int battleMessageDialogHeight;

   unsigned int textMap[128];

   unsigned int dialogLeftBorderIndex;
   unsigned int dialogTopBorderIndex;
   unsigned int dialogRightBorderIndex;
   unsigned int dialogBottomBorderIndex;
   unsigned int dialogTopLeftBorderIndex;
   unsigned int dialogTopRightBorderIndex;
   unsigned int dialogBottomRightBorderIndex;
   unsigned int dialogBottomLeftBorderIndex;
}
dqRenderConfig_t;

dqRenderConfig_t* dqRenderConfig;

void dqRenderConfig_Init();
void dqRenderConfig_Cleanup();

#endif
