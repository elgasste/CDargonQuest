#include "battle_renderer.h"
#include "render_config.h"
#include "dialog_renderer.h"

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

   dqDialogRenderer_DrawBorder( dqRenderConfig->battleMessageDialogPos,
                                dqRenderConfig->battleMessageDialogWidth,
                                dqRenderConfig->battleMessageDialogHeight );
   dqDialogRenderer_ScrollText( textPos,
                                "Imagine this is some crazy battle against zombies and dragons or whatever, and you've got like 1 health left but you can't run away. Sweet, right?!",
                                dqRenderConfig->battleMessageDialogWidth - 2 );
}
