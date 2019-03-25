#include "args.h"

struct optparse_long longopts[] = {
  { "help", '?',
    OPTPARSE_NONE, "Show help message then exit" },
  { "debug", 'd',
    OPTPARSE_NONE, "Show program line numbers while running" },
  { "version", 'V',
    OPTPARSE_NONE, "Show version number then exit" },
  { "verbose", 'v',
    OPTPARSE_NONE, "Show processing steps" },
  { "palette", 'p',
    OPTPARSE_REQUIRED, "Palette function" opt( ARG_DEFAULT_PALETTE, "" ) },
  { "width", 'w',
    OPTPARSE_REQUIRED, "Image width" opt( ARG_DEFAULT_WIDTH , "px" ) },
  { "height", 'h',
    OPTPARSE_REQUIRED, "Image height" opt( ARG_DEFAULT_HEIGHT, "px" ) },
  { "iterate", 'i',
    OPTPARSE_REQUIRED, "Resolution depth" opt( ARG_DEFAULT_ITERATIONS, "" ) },
  { "sample", 's',
    OPTPARSE_REQUIRED, "Antialiasing" opt( ARG_DEFAULT_SAMPLES, "" ) },
  { "threads", 't',
    OPTPARSE_REQUIRED, "Number of CPUs to use" },
  { "plot-cx", 'x',
    OPTPARSE_REQUIRED, "Central x coordinate" opt( ARG_DEFAULT_X, "" ) },
  { "plot-cy", 'y',
    OPTPARSE_REQUIRED, "Central y coordinate" opt( ARG_DEFAULT_Y, "" ) },
  { "zoom", 'z',
    OPTPARSE_REQUIRED, "Zoom factor" opt( ARG_DEFAULT_ZOOM, "" ) },
  { "output", 'o',
    OPTPARSE_REQUIRED, "Image filename" opt( ARG_DEFAULT_FILENAME, "" ) },
  { 0 }
};

void args_init( global_args *args ) {
  args->width = ARG_DEFAULT_WIDTH;
  args->height = ARG_DEFAULT_HEIGHT;
  args->iterations = ARG_DEFAULT_ITERATIONS;
  args->samples = ARG_DEFAULT_SAMPLES;
  args->palette = ARG_DEFAULT_PALETTE;

  args->cx = ARG_DEFAULT_X;
  args->cy = ARG_DEFAULT_Y;
  args->zoom = ARG_DEFAULT_ZOOM;

  args->threads = ARG_DEFAULT_THREADS;
  args->debug = ARG_DEFAULT_DEBUG;
  args->verbose = ARG_DEFAULT_VERBOSE;
  args->version = ARG_DEFAULT_VERSION;
  args->help = ARG_DEFAULT_HELP;

  args->filename = ARG_DEFAULT_FILENAME;
}

void args_parse( char **v, global_args *args ) {
  int key = 0;
  struct optparse options;
  optparse_init( &options, v );
  args_init( args );

  while( (key = optparse_long(&options, longopts, NULL)) != -1 ) {
    char *arg = options.optarg;

    switch( key ) {
      // Options that control fractal rendering parameters
      case 'w':
        if( arg ) args->width = atoi( arg );
        break;
      case 'h':
        if( arg ) args->height = atoi( arg );
        break;
      case 'p':
        if( arg ) args->palette = arg;
        break;
      case 'i':
        if( arg ) args->iterations = atoi( arg );
        break;
      case 's':
        if( arg ) args->samples = atoi( arg );
        break;
      case 'x':
        if( arg ) args->cx = atof( arg );
        break;
      case 'y':
        if( arg ) args->cy = atof( arg );
        break;
      case 'z':
        if( arg ) args->zoom = atof( arg );
        break;

      // Options that affect program behaviour
      case 'd':
        args->debug = true;
        break;
      case 'o':
        if( arg ) args->filename = arg;
        break;
      case 't':
        if( arg ) args->threads = atoi( arg );
        break;
      case 'v':
        args->verbose = true;
        break;
      case '?':
        args->help = true;
        break;
      case 'V':
        args->version = true;
        break;
    }
  }
}

