#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "strings.h"
#include "error.h"

#define SAFE_DELETE( x ) if ( x != NULL ) { free( x ); x = NULL; }
