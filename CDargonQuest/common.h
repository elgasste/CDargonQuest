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

#define LOG_FILE_NAME      "log.txt"

#define MAX_EVENTS         100
#define MAX_EVENT_ARGS     4

#define ENTITY_NAME_SIZE   32

size_t dqTotalMemoryAllocated;
size_t dqTotalMemoryFreed;

void* dqMalloc( size_t size, sfBool track );
void* dqCalloc( size_t count, size_t size, sfBool track );
void dqFree( void* mem, size_t size, sfBool track );
