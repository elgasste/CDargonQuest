#include "common.h"

void* dqMalloc( size_t size, sfBool track )
{
   void* mem = malloc( size );

   if ( !mem )
   {
      dqError_Message( STR_ERROR_MALLOC );
      exit( 1 );
   }

   if ( track )
   {
      dqTotalMemoryAllocated += size;
   }

   return mem;
}

void* dqCalloc( size_t count, size_t size, sfBool track )
{
   void* mem = calloc( count, size );

   if ( !mem )
   {
      dqError_Message( STR_ERROR_MALLOC );
      exit( 1 );
   }

   if ( track )
   {
      dqTotalMemoryAllocated += ( size * count );
   }

   return mem;
}

void dqFree( void* mem, size_t size, sfBool track )
{
   if ( mem )
   {
      free( mem );

      if ( track )
      {
         dqTotalMemoryFreed += size;
      }
   }
}

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
