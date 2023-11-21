#if !defined( DQ_SFML_UTIL_H )
#define DQ_SFML_UTIL_H

sfTexture* dqTexture_CreateFromFile( const char* filePath );
sfSprite* dqSprite_Create();
sfFont* dqFont_CreateFromFile( const char* filePath );
sfText* dqText_Create();
sfRectangleShape* dqRectangleShape_Create();
sfView* dqView_CreateFromRect( sfFloatRect* rect );
sfRenderWindow* dqRenderWindow_Create( sfVideoMode mode, const char* title, sfUint32 style );

void dqTexture_Destroy( sfTexture* texture );
void dqSprite_Destroy( sfSprite* sprite );
void dqFont_Destroy( sfFont* font );
void dqText_Destroy( sfText* text );
void dqRectangleShape_Destroy( sfRectangleShape* rect );
void dqView_Destroy( sfView* view );
void dqRenderWindow_Destroy( sfRenderWindow* window );

#endif
