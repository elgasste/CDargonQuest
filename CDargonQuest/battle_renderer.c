#include "battle_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "dialog_renderer.h"
#include "transition_renderer.h"
#include "menu_renderer.h"
#include "battle.h"
#include "enemy.h"
#include "menu.h"
#include "window.h"

static void dqBattleRenderer_RenderIntroState( sfVector2f* textPos );
static void dqBattleRenderer_RenderSelectActionState();
static void dqBattleRenderer_RenderResultState( sfVector2f* textPos );
static void dqBattleRenderer_DrawEnemy();

void dqBattleRenderer_Init()
{
   dqBattleRenderer = (dqBattleRenderer_t*)dqMalloc( sizeof( dqBattleRenderer_t ), sfTrue );
}

void dqBattleRenderer_Cleanup()
{
   dqFree( dqBattleRenderer, sizeof( dqBattleRenderer_t ), sfTrue );
}

void dqBattleRenderer_Render()
{
   static sfVector2f textPos;

   textPos.x = dqRenderConfig->battleMessageDialogPos.x + dqRenderConfig->dialogSpriteSize;
   textPos.y = dqRenderConfig->battleMessageDialogPos.y + dqRenderConfig->dialogSpriteSize;

   dqDialogRenderer_DrawBorder( &( dqRenderConfig->battleMessageDialogPos ), dqRenderConfig->battleMessageDialogWidth, dqRenderConfig->battleMessageDialogHeight );

   switch ( dqBattle->state )
   {
      case dqBattleStateIntro:
         dqBattleRenderer_RenderIntroState( &textPos );
         break;
      case dqBattleStateSelectAction:
         dqBattleRenderer_RenderSelectActionState();
         break;
      case dqBattleStateResult:
         dqBattleRenderer_RenderResultState( &textPos );
         break;
   }
}

static void dqBattleRenderer_RenderIntroState( sfVector2f* textPos )
{
   if ( !dqTransitionRenderer->fadingIn )
   {
      dqBattleRenderer_DrawEnemy();
      dqDialogRenderer_ScrollText( textPos, dqBattle->introMessage, dqRenderConfig->battleMessageDialogWidth - 2 );
   }
}

static void dqBattleRenderer_RenderSelectActionState()
{
   dqDialogRenderer_DrawBorder( &( dqRenderConfig->battleStatsDialogPos ), dqRenderConfig->battleStatsDialogWidth, dqRenderConfig->battleStatsDialogHeight );

   dqBattleRenderer_DrawEnemy();
   dqMenuRenderer_Render( dqMenuBattleAction );
}

static void dqBattleRenderer_RenderResultState( sfVector2f* textPos )
{
   dqBattleRenderer_DrawEnemy();
   dqDialogRenderer_ScrollText( textPos, dqBattle->resultMessage, dqRenderConfig->battleMessageDialogWidth - 2 );
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
