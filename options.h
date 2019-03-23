#ifndef H_FRACTAL_OPTIONS
#define H_FRACTAL_OPTIONS

#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>

#include "fractal.h"

#define DEFAULT_VERBOSE false
#define DEFAULT_FILENAME "out.png"

#define xstr(x) #x
#define str(x) xstr(x)

#define opt( x,y) " ("str(x)y")"

extern const char *argp_program_version;
extern const char *argp_program_bug_address;

/** Program documentation. */
static char doc_program[] =
  "A simple Mandelbrot Set image generator";

/** A description of the arguments we accept. */
static char doc_args[] = "";

/** The options we understand. */
static struct argp_option options[] = {
  { "debug", 'd',
    0, 0, "Write program line numbers standard output", 0 },
  { "verbose", 'v',
    0, 0, "Write algorithm to standard output", 0 },
  { "palette", 'p',
    "STRING", 0, "Palette function" opt( DEFAULT_COLOUR_BASE, "" ), 0 },
  { "width", 'w',
    "INTEGER", 0, "Image width" opt( DEFAULT_IMAGE_WIDTH, "px" ), 0 },
  { "height", 'h',
    "INTEGER", 0, "Image height" opt (DEFAULT_IMAGE_HEIGHT, "px" ), 0 },
  { "iterate", 'i',
    "INTEGER", 0, "Resolution depth" opt( DEFAULT_ITERATIONS, "" ), 0 },
  { "sample", 's',
    "INTEGER", 0, "Supersample antialiasing" opt( DEFAULT_SAMPLES, "" ), 0 },
  { "threads", 't',
    "INTEGER", 0, "Number of CPUs to use", 0 },
  { "plot-cx", 'x',
    "DECIMAL", 0, "Central coordinate x" opt( DEFAULT_PLOT_X, "" ), 0 },
  { "plot-cy", 'y',
    "DECIMAL", 0, "Central coordinate y" opt( DEFAULT_PLOT_Y, "" ), 0 },
  { "zoom", 'z',
    "DECIMAL", 0, "Zoom factor" opt( DEFAULT_PLOT_ZOOM, "" ), 0 },
  { "output", 'o',
    "FILE",    0, "Image filename" opt( DEFAULT_FILENAME, "" ), 0 },
  { 0 }
};

/** Used by main to communicate with parse_opt. */
struct arguments {
  /** Fractal rendering controls. */
  fractal_parameters *fractal;

  /** Application controls. */
  int threads;
  char *filename;
};

/**
 * Parse a single option.
 *
 * @param key The single-letter command line parameter key value.
 * @param arg The value provided for the command line parameter (if any).
 *
 * @return 0 on success.
 */
error_t parse_opt( int key, char *arg, struct argp_state *state );

/**
 * Sets application default values, not including the fractal configuration.
 *
 * @param arguments Parameters to control threads, output, etc.
 */
void options_init( struct arguments *arguments );

/** Used by argp to process the command line arguments. */
static struct argp argp = {
  options, parse_opt, doc_args, doc_program, NULL, NULL, NULL
};

#endif

