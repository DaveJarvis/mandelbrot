#include "constants.h"
#include "options.h"

const char *argp_program_version = "1.0";
const char *argp_program_bug_address =
  "https://github.com/DaveJarvis/mandelbrot/issues";

error_t parse_opt( int key, char *arg, struct argp_state *state ) {
  struct arguments *arguments = state->input;

  switch( key ) {
    case 'w':
      arguments->width = arg ? atoi( arg ) : DEFAULT_IMAGE_WIDTH;
      break;
    case 'i':
      arguments->iterations = arg ? atoi( arg ) : DEFAULT_ITERATIONS;
      break;
    case 't':
      arguments->threads = arg ? atoi( arg ) : DEFAULT_THREADS;
      break;
    case 'a':
      arguments->plot_r1 = arg ? atof( arg ) : DEFAULT_PLOT_REAL_X1;
      break;
    case 'b':
      arguments->plot_r2 = arg ? atof( arg ) : DEFAULT_PLOT_REAL_X2;
      break;
    case 'y':
      arguments->plot_i1 = arg ? atof( arg ) : DEFAULT_PLOT_IMAG_Y1;
      break;
    case 'z':
      arguments->plot_i2 = arg ? atof( arg ) : DEFAULT_PLOT_IMAG_Y2;
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
  arguments->width = DEFAULT_IMAGE_WIDTH;
  arguments->height = DEFAULT_IMAGE_WIDTH;
  arguments->iterations = DEFAULT_ITERATIONS;
  arguments->threads = DEFAULT_THREADS;
  arguments->plot_r1 = DEFAULT_PLOT_REAL_X1;
  arguments->plot_r2 = DEFAULT_PLOT_REAL_X2;
  arguments->plot_i1 = DEFAULT_PLOT_IMAG_Y1;
  arguments->plot_i2 = DEFAULT_PLOT_IMAG_Y2;
  arguments->filename = DEFAULT_FILENAME;
}

