#include "battle_renderer.h"
#include "render_config.h"
#include "dialog_renderer.h"
#include "transition_renderer.h"
#include "battle.h"

void dqBattleRenderer_Init()
{
   dqBattleRenderer = (dqBattleRenderer_t*)dqMalloc( sizeof( dqBattleRenderer_t ) );
}

void dqBattleRenderer_Cleanup()
{
   dqFree( dqBattleRenderer );
}

void dqBattleRenderer_Render()
{
   static sfVector2f textPos;

   textPos.x = dqRenderConfig->battleMessageDialogPos.x + dqRenderConfig->dialogSpriteSize;
   textPos.y = dqRenderConfig->battleMessageDialogPos.y + dqRenderConfig->dialogSpriteSize;

   dqDialogRenderer_DrawBorder( &( dqRenderConfig->battleMessageDialogPos ),
                                dqRenderConfig->battleMessageDialogWidth,
                                dqRenderConfig->battleMessageDialogHeight );

   if ( dqBattle->state == dqBattleStateIntro )
   {
      if ( !dqTransitionRenderer->fadingIn )
      {
         dqDialogRenderer_ScrollText( &textPos, "You've encountered some enemies or something!", dqRenderConfig->battleMessageDialogWidth - 2 );
      }
   }
   else
   {
      dqDialogRenderer_ScrollText( &textPos, "...and you ran away from them. Wuss.", dqRenderConfig->battleMessageDialogWidth - 2 );
   }
}
