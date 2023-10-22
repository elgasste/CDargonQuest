#pragma once

#pragma warning ( suppress:6011 )

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "strings.h"
#include "error.h"

#define SAFE_DELETE( x ) if ( x != NULL ) { free( x ); x = NULL; }
#define VERIFY_OR_EXIT( x ) if ( !x ) { dqError_ExitWithMessage( STR_ERROR_MEMORY ); }
