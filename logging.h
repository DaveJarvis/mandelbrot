#ifndef __H_LOGGING
#define __H_LOGGING

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "memory.h"
#include "options.h"

/**
 * Conditionally writes a message to standard output. The message will be
 * formatted using printf, so any number of arguments afterwards are possible.
 *
 * @param arguments Command line argument options.
 * @param message Text to write to standard output.
 */
void log_verbose( struct arguments *arguments, char *message, ... );

#endif

