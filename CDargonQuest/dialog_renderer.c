#include "dialog_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "window.h"

void dqDialogRenderer_Init()
{
   dqDialogRenderer = (dqDialogRenderer_t*)dqMalloc( sizeof( dqDialogRenderer_t ) );

   dqDialogRenderer->textureRect.left = 0;
   dqDialogRenderer->textureRect.top = 0;
   dqDialogRenderer->textureRect.width = dqRenderConfig->dialogSpriteSize;
   dqDialogRenderer->textureRect.height = dqRenderConfig->dialogSpriteSize;

   dqDialogRenderer->sprite = sfSprite_create();
   sfSprite_setTexture( dqDialogRenderer->sprite, dqRenderData->dialogTilesetTexture, sfFalse );
   sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
}

void dqDialogRenderer_Cleanup()
{
   sfSprite_destroy( dqDialogRenderer->sprite );

   dqFree( dqDialogRenderer );
}

void dqDialogRenderer_DrawBorder( sfVector2f pos, unsigned int width, unsigned int height )
{
   unsigned int row, col;
   sfVector2f p;

   for ( row = 0; row < height; row++ )
   {
      for ( col = 0; col < width; col++ )
      {
         p.x = pos.x + ( col * dqRenderConfig->dialogSpriteSize );
         p.y = pos.y + ( row * dqRenderConfig->dialogSpriteSize );

         if ( row == 0 )
         {
            if ( col == 0 )
            {
               // upper-left corner
               dqDialogRenderer->textureRect.left = 4 * dqRenderConfig->dialogSpriteSize;
               dqDialogRenderer->textureRect.top = 0;
               sfSprite_setPosition( dqDialogRenderer->sprite, p );
               sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
               dqWindow_DrawSprite( dqDialogRenderer->sprite );
            }
            else if ( col == width - 1 )
            {
               // upper-right corner
               dqDialogRenderer->textureRect.left = 5 * dqRenderConfig->dialogSpriteSize;
               dqDialogRenderer->textureRect.top = 0;
               sfSprite_setPosition( dqDialogRenderer->sprite, p );
               sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
               dqWindow_DrawSprite( dqDialogRenderer->sprite );
            }
            else
            {
               // upper border
               dqDialogRenderer->textureRect.left = dqRenderConfig->dialogSpriteSize;
               dqDialogRenderer->textureRect.top = 0;
               sfSprite_setPosition( dqDialogRenderer->sprite, p );
               sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
               dqWindow_DrawSprite( dqDialogRenderer->sprite );
            }
         }
         else if ( row == height - 1 )
         {
            if ( col == 0 )
            {
               // bottom-left corner
               dqDialogRenderer->textureRect.left = 7 * dqRenderConfig->dialogSpriteSize;
               dqDialogRenderer->textureRect.top = 0;
               sfSprite_setPosition( dqDialogRenderer->sprite, p );
               sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
               dqWindow_DrawSprite( dqDialogRenderer->sprite );
            }
            else if ( col == width - 1 )
            {
               // bottom-right corner
               dqDialogRenderer->textureRect.left = 6 * dqRenderConfig->dialogSpriteSize;
               dqDialogRenderer->textureRect.top = 0;
               sfSprite_setPosition( dqDialogRenderer->sprite, p );
               sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
               dqWindow_DrawSprite( dqDialogRenderer->sprite );
            }
            else
            {
               // bottom border
               dqDialogRenderer->textureRect.left = dqRenderConfig->dialogSpriteSize * 3;
               dqDialogRenderer->textureRect.top = 0;
               sfSprite_setPosition( dqDialogRenderer->sprite, p );
               sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
               dqWindow_DrawSprite( dqDialogRenderer->sprite );
            }
         }
         else if ( col == 0 )
         {
            dqDialogRenderer->textureRect.left = 0;
            dqDialogRenderer->textureRect.top = 0;
            sfSprite_setPosition( dqDialogRenderer->sprite, p );
            sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
            dqWindow_DrawSprite( dqDialogRenderer->sprite );
         }
         else if ( col == width - 1 )
         {
            dqDialogRenderer->textureRect.left = dqRenderConfig->dialogSpriteSize * 2;
            dqDialogRenderer->textureRect.top = 0;
            sfSprite_setPosition( dqDialogRenderer->sprite, p );
            sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
            dqWindow_DrawSprite( dqDialogRenderer->sprite );
         }
         else
         {
            dqDialogRenderer->textureRect.left = dqRenderConfig->dialogSpriteSize * 7;
            dqDialogRenderer->textureRect.top = dqRenderConfig->dialogSpriteSize * 6;
            sfSprite_setPosition( dqDialogRenderer->sprite, p );
            sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
            dqWindow_DrawSprite( dqDialogRenderer->sprite );
         }
      }
   }
}

void dqDialogRenderer_DrawDialogWithText( sfVector2f pos, const char* text, unsigned int width, unsigned int height )
{
   sfVector2f p;
   p.x = pos.x + ( dqRenderConfig->dialogSpriteSize );
   p.y = pos.y + ( dqRenderConfig->dialogSpriteSize );

   if ( !text )
   {
      return;
   }

   dqDialogRenderer_DrawBorder( pos, width, height );

   // MUFFINS: this draws an "A".
   //
   // - we need a function that takes a const char and draws a tile
   dqDialogRenderer->textureRect.left = 0;
   dqDialogRenderer->textureRect.top = 8;
   sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
   sfSprite_setPosition( dqDialogRenderer->sprite, p );

   dqWindow_DrawSprite( dqDialogRenderer->sprite );
}
