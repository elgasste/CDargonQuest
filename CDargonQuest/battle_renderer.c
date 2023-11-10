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
   dqDialogRenderer_DrawDialogWithText( dqRenderConfig->battleMessageDialogPos,
                                        "Imagine this is some crazy battle against zombies and dragons or whatever, and you've got like one health left but you can't run away. Sweet, right?!",
                                        dqRenderConfig->battleMessageDialogWidth,
                                        dqRenderConfig->battleMessageDialogHeight );
}
