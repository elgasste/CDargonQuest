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

#define CHECK_MALLOC( x ) if ( x == NULL ) { dqError_Message( STR_ERROR_MALLOC ); exit( 1 ); }
#define SAFE_DELETE( x ) if ( x != NULL ) { free( x ); x = NULL; }

#define MAX_EVENTS         100
#define MAX_EVENT_ARGS     4
