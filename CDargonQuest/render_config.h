#pragma once

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
   sfColor diagnosticsFontColor;
   sfColor diagnosticsBackgroundColor;
   float diagnosticsWidth;
   float diagnosticsHeight;
   float diagnosticsPadding;
   unsigned int diagnosticsLineWidth;
   float diagnosticsRefreshRate;

   const char* menuFontFilePath;
   unsigned int menuFontSize;
   sfColor menuFontColor;
   const char* menuCaratText;
   float menuCaratOffsetX;
   float menuCaratBlinkRate;

   float titleMenuOffsetX;
   float titleMenuOffsetY;

   sfVector2f overworldViewSize;
   sfVector2f overworldViewOffset;

   sfColor passableOverlayColor;
   sfColor impassableOverlayColor;
   sfColor mapSwapOverlayColor;

   const char* overworldTileTexturePath;
   unsigned int overworldTileTextureColumns;
   unsigned int overworldTileTextureRows;

   const char* playerTexturePath;

   float overworldFadeOutSeconds;
   float overworldStayFadedSeconds;
   float overworldFadeInSeconds;
   const char* cheatFontFilePath;
   unsigned int cheatFontSize;
   float cheatLetterSpacing;
   sfColor cheatFontColor;
}
dqRenderConfig_t;

dqRenderConfig_t* dqRenderConfig;

void dqRenderConfig_Init();
void dqRenderConfig_Cleanup();