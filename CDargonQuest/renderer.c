#include "renderer.h"
#include "render_config.h"
#include "window.h"

void dqRenderer_Render()
{
   sfRenderWindow_clear( dqWindow, dqRenderConfig->windowClearColor );
   sfRenderWindow_display( dqWindow );
}
