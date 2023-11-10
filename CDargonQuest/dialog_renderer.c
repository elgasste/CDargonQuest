#include "dialog_renderer.h"
#include "render_config.h"
#include "render_data.h"
#include "window.h"

static unsigned int dqDialogRenderer_GetTileIdForChar( char c )
{
   if ( c >= 'A' && c <= 'Z' )
   {
      // capital letters start at 65 in the ASCII table, and at index 9 in the tileset
      return (unsigned int)c - 56;
   }
   else if ( c >= 'a' && c <= 'z' )
   {
      // lower case letters start at 97 in the ASCII table, and at index 35 in the tileset
      return (unsigned int)c - 62;
   }
   else
   {
      switch ( c )
      {
         case ' ': return 61;
         case '!': return 62;
         case '"': return 63;
         case '\'': return 64;
         case '?': return 65;
         case '(': return 66;
         case ')': return 67;
         case '-': return 68;
         case ',': return 69;
         case '.': return 70;
         case '*': return 71;
      }
   }

   // default to space
   return 61;
}

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
   int i, j;
   char c, peek;
   unsigned int tileIndex, textIndex, peekIndex, textureX, textureY;
   sfBool skip;
   sfVector2f p;

   p.x = pos.x + ( dqRenderConfig->dialogSpriteSize );
   p.y = pos.y + ( dqRenderConfig->dialogSpriteSize );

   dqDialogRenderer_DrawBorder( pos, width, height );

   if ( !text )
   {
      return;
   }

   for ( textIndex = 0, i = 1, j = 1; ; i++, textIndex++ )
   {
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
            if ( i + ( peekIndex - textIndex ) >= ( width - 2 ) )
            {
               i = 0;
               j++;
               skip = sfTrue;
            }

            break;
         }
      }

      if ( !skip )
      {
         tileIndex = dqDialogRenderer_GetTileIdForChar( c );
         textureX = tileIndex % dqRenderConfig->dialogTileTextureColumns;
         textureY = tileIndex / dqRenderConfig->dialogTileTextureColumns;

         dqDialogRenderer->textureRect.left = textureX * dqRenderConfig->dialogSpriteSize;
         dqDialogRenderer->textureRect.top = textureY * dqRenderConfig->dialogSpriteSize;
         p.x = pos.x + ( i * dqRenderConfig->dialogSpriteSize );
         p.y = pos.y + ( j * dqRenderConfig->dialogSpriteSize );

         sfSprite_setTextureRect( dqDialogRenderer->sprite, dqDialogRenderer->textureRect );
         sfSprite_setPosition( dqDialogRenderer->sprite, p );
         dqWindow_DrawSprite( dqDialogRenderer->sprite );
      }
   }
}
