#include "constants.h"
#include "options.h"

const char *argp_program_version = "1.0.0";
const char *argp_program_bug_address =
  "https://github.com/DaveJarvis/mandelbrot/issues";

error_t parse_opt( int key, char *arg, struct argp_state *state ) {
  struct arguments *arguments = state->input;

  switch( key ) {
    case 'v':
      arguments->verbose = true;
      break;
    case 'w':
      arguments->width = arg ? atoi( arg ) : DEFAULT_IMAGE_WIDTH;
      break;
    case 'h':
      arguments->height = arg ? atoi( arg ) : DEFAULT_IMAGE_HEIGHT;
      break;
    case 'i':
      arguments->iterations = arg ? atoi( arg ) : DEFAULT_ITERATIONS;
      break;
    case 't':
      arguments->threads = arg ? atoi( arg ) : DEFAULT_THREADS;
      break;
    case 'x':
      arguments->cx = arg ? atof( arg ) : DEFAULT_PLOT_X;
      break;
    case 'y':
      arguments->cy = arg ? atof( arg ) : DEFAULT_PLOT_Y;
      break;
    case 'z':
      arguments->zoom = arg ? atof( arg ) : DEFAULT_PLOT_ZOOM;
      break;
    case 'o':
      arguments->filename = arg;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

void options_init( struct arguments *arguments ) {
  arguments->verbose = DEFAULT_VERBOSE;
  arguments->width = DEFAULT_IMAGE_WIDTH;
  arguments->height = DEFAULT_IMAGE_HEIGHT;
  arguments->iterations = DEFAULT_ITERATIONS;
  arguments->threads = DEFAULT_THREADS;
  arguments->cx = DEFAULT_PLOT_X;
  arguments->cy = DEFAULT_PLOT_Y;
  arguments->zoom = DEFAULT_PLOT_ZOOM;
  arguments->filename = DEFAULT_FILENAME;
}

