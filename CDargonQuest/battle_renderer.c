#include "battle_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "game_data.h"
#include "dialog_renderer.h"
#include "transition_renderer.h"
#include "menu_renderer.h"
#include "battle.h"
#include "enemy.h"
#include "player.h"
#include "battle_stats.h"
#include "menu.h"
#include "window.h"

static void dqBattleRenderer_RenderIntroState();
static void dqBattleRenderer_RenderSelectActionState();
static void dqBattleRenderer_RenderResultState();
static void dqBattleRenderer_DrawEnemy();
static void dqBattleRenderer_DrawMessageBorder();
static void dqBattleRenderer_DrawActionMenuBorder();

void dqBattleRenderer_Init()
{
   dqBattleRenderer = (dqBattleRenderer_t*)dqMalloc( sizeof( dqBattleRenderer_t ), sfTrue );

   dqBattleRenderer->backdropRect = dqRectangleShape_Create();
   sfRectangleShape_setPosition( dqBattleRenderer->backdropRect, dqRenderConfig->overworldViewOffset );
   sfRectangleShape_setSize( dqBattleRenderer->backdropRect, dqRenderConfig->overworldViewSize );
   sfRectangleShape_setFillColor( dqBattleRenderer->backdropRect, dqRenderConfig->battleBackdropColor );

   dqBattleRenderer->messageTextPos.x = dqRenderConfig->battleMessageDialogPos.x + dqRenderConfig->dialogSpriteSize;
   dqBattleRenderer->messageTextPos.y = dqRenderConfig->battleMessageDialogPos.y + dqRenderConfig->dialogSpriteSize;
}

void dqBattleRenderer_Cleanup()
{
   dqRectangleShape_Destroy( dqBattleRenderer->backdropRect );

   dqFree( dqBattleRenderer, sizeof( dqBattleRenderer_t ), sfTrue );
}

void dqBattleRenderer_Render()
{
   dqWindow_DrawRectangleShape( dqBattleRenderer->backdropRect );

   switch ( dqBattle->state )
   {
      case dqBattleStateIntro:
         dqBattleRenderer_RenderIntroState();
         break;
      case dqBattleStateSelectAction:
         dqBattleRenderer_RenderSelectActionState();
         break;
      case dqBattleStateResult:
         dqBattleRenderer_RenderResultState();
         break;
   }
}

static void dqBattleRenderer_RenderIntroState()
{
   if ( !dqTransitionRenderer->fadingIn )
   {
      dqBattleRenderer_DrawMessageBorder();
      dqBattleRenderer_DrawEnemy();
      dqDialogRenderer_ScrollText( &( dqBattleRenderer->messageTextPos ),
                                   dqBattle->introMessage,
                                   dqRenderConfig->battleMessageDialogWidth - 2 );
   }
}

static void dqBattleRenderer_RenderSelectActionState()
{
   static sfVector2f statsTextPos;
   static char statStr[16];
   dqPlayer_t* player = dqGameData->player;

   dqDialogRenderer_DrawBorder( &( dqRenderConfig->battleStatsDialogPos ),
                                dqRenderConfig->battleStatsDialogWidth,
                                dqRenderConfig->battleStatsDialogHeight );

   statsTextPos.x = dqRenderConfig->battleStatsDialogPos.x + dqRenderConfig->dialogSpriteSize;
   statsTextPos.y = dqRenderConfig->battleStatsDialogPos.y + dqRenderConfig->dialogSpriteSize;
   dqDialogRenderer_DrawText( &statsTextPos, player->name, PLAYER_NAME_LENGTH - 1 );

   sprintf_s( statStr, 16, "HP: %u", player->battleStats->hitPoints );
   statsTextPos.x += dqRenderConfig->dialogSpriteSize;
   statsTextPos.y += dqRenderConfig->dialogSpriteSize * 2;
   dqDialogRenderer_DrawText( &statsTextPos, statStr, 15 );

   sprintf_s( statStr, 16, "MP: %u", player->battleStats->magicPoints );
   statsTextPos.y += dqRenderConfig->dialogSpriteSize;
   dqDialogRenderer_DrawText( &statsTextPos, statStr, 15 );

   dqBattleRenderer_DrawEnemy();

   dqBattleRenderer_DrawActionMenuBorder();
   dqMenuRenderer_Render( dqMenuBattleAction );
}

static void dqBattleRenderer_RenderResultState()
{
   dqBattleRenderer_DrawEnemy();
   dqBattleRenderer_DrawMessageBorder();
   dqDialogRenderer_ScrollText( &( dqBattleRenderer->messageTextPos ),
                                dqBattle->resultMessage,
                                dqRenderConfig->battleMessageDialogWidth - 2 );
}

static void dqBattleRenderer_DrawEnemy()
{
   static sfVector2f enemySpritePos;

   if ( dqBattle->enemy )
   {
      enemySpritePos.x = ( dqRenderConfig->screenWidth / 2 ) - ( (float)( dqRenderConfig->enemySpriteWidths[dqBattle->enemy->spriteSize] ) / 2 );
      enemySpritePos.y = dqRenderConfig->enemyAreaPosY;
      sfSprite_setPosition( dqBattle->enemy->sprite, enemySpritePos );
      dqWindow_DrawSprite( dqBattle->enemy->sprite );
   }
}

static void dqBattleRenderer_DrawMessageBorder()
{
   dqDialogRenderer_DrawBorder( &( dqRenderConfig->battleMessageDialogPos ),
                                dqRenderConfig->battleMessageDialogWidth,
                                dqRenderConfig->battleMessageDialogHeight );
}

static void dqBattleRenderer_DrawActionMenuBorder()
{
   dqDialogRenderer_DrawBorder( &( dqRenderConfig->battleActionMenuDialogPos ),
                                dqRenderConfig->battleActionMenuDialogWidth,
                                dqRenderConfig->battleActionMenuDialogHeight );
}
