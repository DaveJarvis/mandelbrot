#ifndef H_FRACTAL_ARGS
#define H_FRACTAL_ARGS

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "optparse.h"

#define UNUSED __attribute__((unused))

#define ARG_UNDEFINED 0L

#define ARG_DEFAULT_WIDTH 1024
#define ARG_DEFAULT_HEIGHT 768
#define ARG_DEFAULT_ITERATIONS 50
#define ARG_DEFAULT_SAMPLES 1

#define ARG_DEFAULT_X    -0.75
#define ARG_DEFAULT_Y     0.00
#define ARG_DEFAULT_ZOOM  300

#define ARG_DEFAULT_PALETTE "hsv(215.7,0.987,0.694)"

#define ARG_DEFAULT_DEBUG false
#define ARG_DEFAULT_VERBOSE false
#define ARG_DEFAULT_VERSION false
#define ARG_DEFAULT_HELP false

#define ARG_DEFAULT_THREADS ARG_UNDEFINED
#define ARG_DEFAULT_FILENAME "output.png"

#define xstr(x) #x
#define str(x) xstr(x)

#define opt( x,y) " ("str(x)y")"

/** List of command line arguments to parse into global_args structure. */
extern struct optparse_long longopts[];

typedef struct global_args_t {
  /** Canvas width in pixels (-w, --width) */
  int width;
  /** Canvas height in pixels (-h, --height) */
  int height;

  /** How many iterations to test for escaping to infinity (-i, --iterate) */
  int iterations;
  /** Number of neighbouring pixels to subsample (-s, --sample) */
  int samples;

  /** Central x coordinate for fractal zoom (-x, --plot-cx) */
  double cx;
  /** Central y coordinate for fractal zoom (-y, --plot-cy) */
  double cy;
  /** Zoom into (cx, cy) by this amount (-z, --zoom) */
  double zoom;

  /** Palette colouring (-p, --palette) */
  char *palette;

  /** Output filename (-o, --output) */
  char *filename;

  /** Number of threads (-t, --threads) */
  int threads;

  /** Write extended process information (-d, --debug) */
  bool debug;
  /** Write process information to standard output (-v, --verbose) */
  bool verbose;
  /** Show version (-V, --version) */
  bool version;
  /** Show help (-?, --help) */
  bool help;
} global_args;

void args_init( global_args *args );

/**
 * Sets application default values, not including the fractal configuration.
 *
 * @param v Unparsed command line arguments from main.
 * @param args Parameters to control threads, output, etc.
 */
void args_parse( char **v, global_args *args );

#endif

