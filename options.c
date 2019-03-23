#include "options.h"
#include "logging.h"

const char *argp_program_version = "1.0.0";
const char *argp_program_bug_address =
  "https://github.com/DaveJarvis/mandelbrot/issues";

error_t parse_opt( int key, char *arg, struct argp_state *state ) {
  struct arguments *arguments = state->input;
  mandelbrot_parameters *fractal = arguments->fractal;

  switch( key ) {
    // Options that control fractal rendering parameters
    case 'w':
      fractal->width = arg ? atoi( arg ) : DEFAULT_IMAGE_WIDTH;
      break;
    case 'h':
      fractal->height = arg ? atoi( arg ) : DEFAULT_IMAGE_HEIGHT;
      break;
    case 'i':
      fractal->iterations = arg ? atoi( arg ) : DEFAULT_ITERATIONS;
      break;
    case 's':
      fractal->samples = arg ? atoi( arg ) : DEFAULT_SAMPLES;
      break;
    case 'x':
      fractal->cx = arg ? atof( arg ) : DEFAULT_PLOT_X;
      break;
    case 'y':
      fractal->cy = arg ? atof( arg ) : DEFAULT_PLOT_Y;
      break;
    case 'z':
      fractal->zoom = arg ? atof( arg ) : DEFAULT_PLOT_ZOOM;
      break;

    // Options that affect program behaviour
    case 'd':
      logging_set_level( LOG_DEBUG );
      break;
    case 'o':
      arguments->filename = arg;
      break;
    case 't':
      arguments->threads = arg ? atoi( arg ) : DEFAULT_THREADS;
      break;
    case 'v':
      logging_set_level( LOG_INFO );
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

void options_init( struct arguments *arguments ) {
  arguments->filename = DEFAULT_FILENAME;
  arguments->threads = DEFAULT_THREADS;
}

