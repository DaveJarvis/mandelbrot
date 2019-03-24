#ifndef H_FRACTAL_SETTINGS
#define H_FRACTAL_SETTINGS

#include <stdnoreturn.h>

#include "args.h"
#include "logging.h"
#include "optparse.h"

#define SETTINGS_EXIT_LEVEL_VERSION 2
#define SETTINGS_EXIT_LEVEL_HELP 3

/**
 * Responsible for interpreting post-parsed command line parameters. This
 * will set the log level, show help, show version information, etc.
 *
 * @param argv The command line arguments before processing.
 * @param args The command line arguments structure.
 */
void settings_interpret( char **argv, global_args *args );

/**
 * Exits the application, nothing written to the console.
 *
 * @param exit_level Program exit level.
 */
noreturn void settings_terminate( int exit_level );

/**
 * Write the version number to standard output then exit.
 */
void settings_show_version( void );

/**
 * Write usage to standard output then exit.
 *
 * @param program Name of the program being run (argsv[0]).
 */
void settings_show_help( char *program );

#endif

