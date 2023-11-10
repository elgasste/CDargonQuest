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
                                        "Hi!!",
                                        dqRenderConfig->battleMessageDialogWidth,
                                        dqRenderConfig->battleMessageDialogHeight );
}
