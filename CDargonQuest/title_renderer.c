#include "title_renderer.h"
#include "render_config.h"
#include "menu.h"
#include "menu_renderer.h"
#include "window.h"

void dqTitleRenderer_Init()
{
   sfVector2f backdropPos = { 0, 0 };
   sfVector2f backdropSize = { dqRenderConfig->screenWidth, dqRenderConfig->screenHeight };

   dqTitleRenderer = (dqTitleRenderer_t*)dqMalloc( sizeof( dqTitleRenderer_t ), sfTrue );

   dqTitleRenderer->backdropRect = dqRectangleShape_Create();
   sfRectangleShape_setPosition( dqTitleRenderer->backdropRect, backdropPos );
   sfRectangleShape_setSize( dqTitleRenderer->backdropRect, backdropSize );
   sfRectangleShape_setFillColor( dqTitleRenderer->backdropRect, dqRenderConfig->battleBackdropColor );
}

void dqTitleRenderer_Cleanup()
{
   dqRectangleShape_Destroy( dqTitleRenderer->backdropRect );

   dqFree( dqTitleRenderer, sizeof( dqTitleRenderer_t ), sfTrue );
}

void dqTitleRenderer_Render()
{
   dqWindow_DrawRectangleShape( dqTitleRenderer->backdropRect );
   dqMenuRenderer_Render( dqMenuTitle );
}
