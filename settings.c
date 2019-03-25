#include "settings.h"

/** Program documentation. */
const char *PROGRAM_NAME = "A fractal image generator";
const char *PROGRAM_VERSION = "1.0.0";
const char *PROGRAM_ISSUES = "https://github.com/DaveJarvis/mandelbrot/issues";

void settings_interpret( char **v, global_args *args ) {
  if( args->verbose ) {
    logging_set_level( LOG_POSTS );
  }

  if( args->debug ) {
    logging_set_level( LOG_DEBUG );
  }

  if( args->version ) {
    settings_show_version();
    settings_terminate( SETTINGS_EXIT_LEVEL_VERSION );
  }

  if( args->help ) {
    settings_show_help( v[0] );
    settings_terminate( SETTINGS_EXIT_LEVEL_HELP );
  }
}

noreturn void settings_terminate( int exit_level ) {
  exit( exit_level );
}

void settings_show_version( void ) {
  printf( "%s\n", PROGRAM_VERSION );
}

void settings_show_help( char *program ) {
  printf( "%s\n\n", PROGRAM_NAME );
  printf( "Usage: %s [OPTION...]\n", program );
  printf( "Where [OPTION] includes:\n" );
  
  for( int i = 0; !optparse_longopts_end( longopts, i ); i++) {
    const struct optparse_long *opt = &longopts[i];
    printf( "  -%c, --%-10s %s\n",
      opt->shortname, opt->longname, opt->description );
  }

  printf( "\nReport issues at: %s\n", PROGRAM_ISSUES );
}

