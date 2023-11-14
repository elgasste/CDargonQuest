#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <SFML/Graphics.h>

#include "strings.h"
#include "error.h"
#include "log.h"

#define MAX_EVENTS         100
#define MAX_EVENT_ARGS     4

#define ENTITY_NAME_SIZE   32

void* dqMalloc( size_t size );
void* dqCalloc( size_t count, size_t size );
void dqFree( void* mem );
