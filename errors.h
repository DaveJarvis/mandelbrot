#ifndef H_FRACTAL_ERRORS
#define H_FRACTAL_ERRORS

#include <stdlib.h>
#include <stdio.h>
#include <stdnoreturn.h>

#define ERROR_MEMORY 1
#define ERROR_MEMORY_TEXT "Out of memory"

/**
 * Exits the application with the given error level.
 *
 * @param exit_code The program exit code.
 * @param message The error message to write to standard error.
 */
noreturn void error_terminate( int exit_code, char *message );

#endif

