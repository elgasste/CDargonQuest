#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <SFML/Graphics.h>

#include "strings.h"
#include "error.h"

#define SAFE_DELETE( x ) if ( x != NULL ) { free( x ); x = NULL; }

#define MAX_EVENTS         100
#define MAX_EVENT_ARGS     4
