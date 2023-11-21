#if !defined( DQ_TITLE_RENDERER_H )
#define DQ_TITLE_RENDERER_H

#include "common.h"

typedef struct dqTitleRenderer_t
{
   sfRectangleShape* backdropRect;
}
dqTitleRenderer_t;

dqTitleRenderer_t* dqTitleRenderer;

void dqTitleRenderer_Init();
void dqTitleRenderer_Cleanup();
void dqTitleRenderer_Render();

#endif
