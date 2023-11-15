#include "battle_renderer.h"
#include "render_config.h"
#include "dialog_renderer.h"
#include "transition_renderer.h"
#include "menu_renderer.h"
#include "battle.h"
#include "menu.h"

static void dqBattleRenderer_RenderIntroState( sfVector2f* textPos );
static void dqBattleRenderer_RenderSelectActionState();
static void dqBattleRenderer_RenderResultState( sfVector2f* textPos );

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
      dqDialogRenderer_ScrollText( textPos, dqBattle->introMessage, dqRenderConfig->battleMessageDialogWidth - 2 );
   }
}

static void dqBattleRenderer_RenderSelectActionState()
{
   dqMenuRenderer_Render( dqMenuBattleAction );
}

static void dqBattleRenderer_RenderResultState( sfVector2f* textPos )
{
   dqDialogRenderer_ScrollText( textPos, dqBattle->resultMessage, dqRenderConfig->battleMessageDialogWidth - 2 );
}
