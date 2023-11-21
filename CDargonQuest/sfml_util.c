#include "common.h"

sfTexture* dqTexture_CreateFromFile( const char* filePath )
{
   dqTotalSfmlObjectsCreated++;
   return sfTexture_createFromFile( filePath, 0 );
}

sfSprite* dqSprite_Create()
{
   dqTotalSfmlObjectsCreated++;
   return sfSprite_create();
}

sfFont* dqFont_CreateFromFile( const char* filePath )
{
   dqTotalSfmlObjectsCreated++;
   return sfFont_createFromFile( filePath );
}

sfText* dqText_Create()
{
   dqTotalSfmlObjectsCreated++;
   return sfText_create();
}

sfRectangleShape* dqRectangleShape_Create()
{
   dqTotalSfmlObjectsCreated++;
   return sfRectangleShape_create();
}

sfView* dqView_CreateFromRect( sfFloatRect* rect )
{
   dqTotalSfmlObjectsCreated++;
   return sfView_createFromRect( *rect );
}

sfRenderWindow* dqRenderWindow_Create( sfVideoMode mode, const char* title, sfUint32 style )
{
   dqTotalSfmlObjectsCreated++;
   return sfRenderWindow_create( mode, title, style, 0 );
}

void dqTexture_Destroy( sfTexture* texture )
{
   dqTotalSfmlObjectsDestroyed++;
   sfTexture_destroy( texture );
}

void dqSprite_Destroy( sfSprite* sprite )
{
   dqTotalSfmlObjectsDestroyed++;
   sfSprite_destroy( sprite );
}

void dqFont_Destroy( sfFont* font )
{
   dqTotalSfmlObjectsDestroyed++;
   sfFont_destroy( font );
}

void dqText_Destroy( sfText* text )
{
   dqTotalSfmlObjectsDestroyed++;
   sfText_destroy( text );
}

void dqRectangleShape_Destroy( sfRectangleShape* rect )
{
   dqTotalSfmlObjectsDestroyed++;
   sfRectangleShape_destroy( rect );
}

void dqView_Destroy( sfView* view )
{
   dqTotalSfmlObjectsDestroyed++;
   sfView_destroy( view );
}

void dqRenderWindow_Destroy( sfRenderWindow* window )
{
   dqTotalSfmlObjectsDestroyed++;
   sfRenderWindow_destroy( window );
}
