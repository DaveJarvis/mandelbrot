#ifndef __H_ERRORS
#define __H_ERRORS

#include <stdlib.h>
#include <stdio.h>

#define ERROR_MEMORY 1
#define ERROR_MEMORY_TEXT "Out of memory"

/**
 * Exits the application with the given error level.
 *
 * @param error_level The program exit code.
 * @param message The error message to write to standard error.
 */
void error_terminate( int error_level, char *message );

#endif

