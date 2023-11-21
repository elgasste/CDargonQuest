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
#include "sfml_util.h"

#define LOG_FILE_NAME      "log.txt"

#define MAX_EVENTS         100
#define MAX_EVENT_ARGS     4

#define PLAYER_NAME_SIZE   9
#define ENTITY_NAME_SIZE   32

size_t dqTotalMemoryAllocated;
size_t dqTotalMemoryFreed;

unsigned int dqTotalSfmlObjectsCreated;
unsigned int dqTotalSfmlObjectsDestroyed;

#endif
