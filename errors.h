#ifndef H_FRACTAL_ERRORS
#define H_FRACTAL_ERRORS

#include <stdlib.h>
#include <stdio.h>
#include <stdnoreturn.h>

#define ERROR_MEMORY 1
#define ERROR_MEMORY_TEXT "Out of memory"

#define ERROR_THREAD 2
#define ERROR_THREAD_TEXT "Cannot create fractal rendering threads"

/**
 * Exits the application with the given exit code.
 *
 * @param exit_code The program error level.
 * @param message The reason for termination (written to standard error).
 */
noreturn void error_terminate( int exit_code, char *message );

#endif

