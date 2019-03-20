#ifndef __H_OPTIONS
#define __H_OPTIONS

#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>

#include "constants.h"
#include "image.h"

#define xstr(x) #x
#define str(x) xstr(x)

#define opt( x,y) " ("str(x)y")"

extern const char *argp_program_version;
extern const char *argp_program_bug_address;

/* Program documentation. */
static char doc_program[] =
  "A simple Mandelbrot Set image generator";

/* A description of the arguments we accept. */
static char doc_args[] = "-w -h -i -a -b -y -z -o";

/* The options we understand. */
static struct argp_option options[] = {
  { "width",   'w', "INTEGER", 0,
    "Image width" opt( DEFAULT_IMAGE_WIDTH, "px" ) },
  { "height",  'h', "INTEGER", 0,
    "Image height" opt( DEFAULT_IMAGE_HEIGHT, "px" ) },
  { "iterate", 'i', "INTEGER", 0,
    "Resolution depth" opt( DEFAULT_ITERATIONS, "" ) },
  { "threads", 't', "INTEGER", 0,
    "Number of CPUs to use" },
  { "plot-r1", 'a', "DECIMAL", 0,
    "Leftmost real coord" opt( DEFAULT_PLOT_REAL_X1, "" )  },
  { "plot-r2", 'b', "DECIMAL", 0,
    "Rightmost real coord" opt( DEFAULT_PLOT_REAL_X2, "" ) },
  { "plot-i1", 'y', "DECIMAL", 0,
    "Topmost imaginary coord" opt( DEFAULT_PLOT_IMAG_Y1, "" ) },
  { "plot-i2", 'z', "DECIMAL", 0,
    "Bottommost imaginary coord" opt( DEFAULT_PLOT_IMAG_Y2, "" ) },
  { "output",  'o', "FILE",    0,
    "Image filename" opt( DEFAULT_FILENAME, "" ) },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments {
  int width, height, iterations, threads;
  double plot_r1, plot_r2;
  double plot_i1, plot_i2;
  char *filename;
};

/**
 * Parse a single option.
 */
error_t parse_opt( int key, char *arg, struct argp_state *state );

static struct argp argp = { options, parse_opt, doc_args, doc_program };

/**
 * Sets structure elements to default values.
 */
void options_init( struct arguments *arguments );

#endif

