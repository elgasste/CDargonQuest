#if !defined( DQ_COMMON_H )
#define DQ_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <SFML/Graphics.h>

#include "strings.h"
#include "error.h"
#include "log.h"
#include "mem_util.h"

#define LOG_FILE_NAME      "log.txt"

#define MAX_EVENTS         100
#define MAX_EVENT_ARGS     4

#define PLAYER_NAME_SIZE   9
#define ENTITY_NAME_SIZE   32

size_t dqTotalMemoryAllocated;
size_t dqTotalMemoryFreed;

unsigned int dqTotalSfmlObjectsCreated;
unsigned int dqTotalSfmlObjectsDestroyed;

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
