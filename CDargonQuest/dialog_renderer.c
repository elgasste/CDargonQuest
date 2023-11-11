#include "dialog_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "clock.h"
#include "window.h"

void dqDialogRenderer_Init()
{
   dqDialogRenderer = (dqDialogRenderer_t*)dqMalloc( sizeof( dqDialogRenderer_t ) );

   dqDialogRenderer_ResetScroll();

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

void dqDialogRenderer_ResetScroll()
{
   dqDialogRenderer->isScrolling = sfFalse;
   dqDialogRenderer->hasScrolled = sfFalse;
   dqDialogRenderer->scrollElapsedSeconds = 0;
   dqDialogRenderer->scrollCharCount = 0;
}

void dqDialogRenderer_DrawBorder( sfVector2f* pos, unsigned int width, unsigned int height )
{
   unsigned int row, col, idx;
   static sfVector2f p;

   for ( row = 0; row < height; row++ )
   {
      for ( col = 0; col < width; col++ )
      {
         p.x = pos->x + ( col * dqRenderConfig->dialogSpriteSize );
         p.y = pos->y + ( row * dqRenderConfig->dialogSpriteSize );

         if ( row == 0 )
         {
            idx = ( col == 0 )         ? dqRenderConfig->dialogTopLeftBorderIndex :
                  ( col == width - 1 ) ? dqRenderConfig->dialogTopRightBorderIndex :
                                         dqRenderConfig->dialogTopBorderIndex;
         }
         else if ( row == height - 1 )
         {
            idx = ( col == 0 )         ? dqRenderConfig->dialogBottomLeftBorderIndex :
                  ( col == width - 1 ) ? dqRenderConfig->dialogBottomRightBorderIndex :
                                         dqRenderConfig->dialogBottomBorderIndex;
         }
         else
         {
            idx = ( col == 0 )         ? dqRenderConfig->dialogLeftBorderIndex :
                  ( col == width - 1 ) ? dqRenderConfig->dialogRightBorderIndex :
                                         dqRenderConfig->textMap[' '];
         }

         dqDialogRenderer->textureRect.left = ( idx % dqRenderConfig->dialogTileTextureColumns ) * dqRenderConfig->dialogSpriteSize;
         dqDialogRenderer->textureRect.top = ( idx / dqRenderConfig->dialogTileTextureColumns ) * dqRenderConfig->dialogSpriteSize;

         sfSprite_setPosition( dqDialogRenderer->sprite, p );
         sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
         dqWindow_DrawSprite( dqDialogRenderer->sprite );
      }
   }
}

static void dqDialogRenderer_DrawTextPortion( sfVector2f* pos, const char* text, unsigned int width, unsigned int charCount )
{
   int i, j;
   char c, peek;
   unsigned int tileIndex, textIndex, peekIndex, textureX, textureY;
   sfBool skip;
   static sfVector2f p;

   if ( !text )
   {
      return;
   }

   for ( textIndex = 0, i = 0, j = 0; ; i++, textIndex++ )
   {
      if ( textIndex >= charCount )
      {
         break;
      }

      c = text[textIndex];
      skip = sfFalse;

      if ( c == '\0' )
      {
         break;
      }

      for ( peekIndex = textIndex + 1; ; peekIndex++ )
      {
         peek = text[peekIndex];

         if ( peek == ' ' || peek == '\0' )
         {
            // TODO: if a single word is wider than the dialog, do we need to worry?
            if ( i + ( peekIndex - textIndex ) > width )
            {
               i = -1;
               j++;
               skip = sfTrue;
            }

            break;
         }
      }

      if ( !skip )
      {
         tileIndex = dqRenderConfig->textMap[c];
         textureX = tileIndex % dqRenderConfig->dialogTileTextureColumns;
         textureY = tileIndex / dqRenderConfig->dialogTileTextureColumns;

         dqDialogRenderer->textureRect.left = textureX * dqRenderConfig->dialogSpriteSize;
         dqDialogRenderer->textureRect.top = textureY * dqRenderConfig->dialogSpriteSize;
         p.x = pos->x + ( i * dqRenderConfig->dialogSpriteSize );
         p.y = pos->y + ( j * dqRenderConfig->dialogSpriteSize );

         sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
         sfSprite_setPosition( dqDialogRenderer->sprite, p );
         dqWindow_DrawSprite( dqDialogRenderer->sprite );
      }
   }
}

void dqDialogRenderer_DrawText( sfVector2f* pos, const char* text, unsigned int width )
{
   dqDialogRenderer_DrawTextPortion( pos, text, width, (unsigned int)strlen( text ) );
}

void dqDialogRenderer_ScrollText( sfVector2f* pos, const char* text, unsigned int width )
{
   unsigned int textLength;

   if ( dqDialogRenderer->hasScrolled )
   {
      dqDialogRenderer_DrawText( pos, text, width );
   }
   else
   {
      dqDialogRenderer->scrollElapsedSeconds += dqClock->lastFrameSeconds;
      dqDialogRenderer->scrollCharCount = (unsigned int)( dqDialogRenderer->scrollElapsedSeconds / dqRenderConfig->dialogScrollCharSeconds );

      textLength = (unsigned int)strlen( text );

      if ( dqDialogRenderer->scrollCharCount >= textLength )
      {
         dqDialogRenderer->isScrolling = sfFalse;
         dqDialogRenderer->hasScrolled = sfTrue;
         dqDialogRenderer->scrollCharCount = textLength;
      }
      else
      {
         dqDialogRenderer->isScrolling = sfTrue;
      }

      dqDialogRenderer_DrawTextPortion( pos, text, width, dqDialogRenderer->scrollCharCount );
   }
}
