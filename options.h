#ifndef H_MANDELBROT_OPTIONS
#define H_MANDELBROT_OPTIONS

#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>

#include "constants.h"

#define xstr(x) #x
#define str(x) xstr(x)

#define opt( x,y) " ("str(x)y")"

extern const char *argp_program_version;
extern const char *argp_program_bug_address;

/* Program documentation. */
static char doc_program[] =
  "A simple Mandelbrot Set image generator";

/* A description of the arguments we accept. */
static char doc_args[] = "";

/* The options we understand. */
static struct argp_option options[] = {
  { "verbose", 'v',
    0, 0, "Write algorithmic details to standard output", 0 },
  { "width", 'w',
    "INTEGER", 0, "Image width" opt(DEFAULT_IMAGE_WIDTH, "px"), 0 },
  { "height", 'h',
    "INTEGER", 0, "Image height" opt(DEFAULT_IMAGE_HEIGHT, "px"), 0 },
  { "iterate", 'i',
    "INTEGER", 0, "Resolution depth" opt(DEFAULT_ITERATIONS, ""), 0 },
  { "threads", 't',
    "INTEGER", 0, "Number of CPUs to use", 0 },
  { "plot-r1", 'a',
    "DECIMAL", 0, "Left real coord" opt(DEFAULT_PLOT_REAL_X1, ""), 0 },
  { "plot-r2", 'b',
    "DECIMAL", 0, "Right real coord" opt(DEFAULT_PLOT_REAL_X2, ""), 0 },
  { "plot-i1", 'y',
    "DECIMAL", 0, "Top imaginary coord" opt(DEFAULT_PLOT_IMAG_Y1, ""), 0 },
  { "plot-i2", 'z',
    "DECIMAL", 0, "Bottom imaginary coord" opt(DEFAULT_PLOT_IMAG_Y2, ""), 0 },
  { "output", 'o',
    "FILE",    0, "Image filename" opt(DEFAULT_FILENAME, ""), 0 },
  { 0 }
};

typedef unsigned long mthread_t;

/* Used by main to communicate with parse_opt. */
struct arguments {
  int width, height;
  double plot_r1, plot_r2;
  double plot_i1, plot_i2;
  int threads, iterations;
  char *filename;
  bool verbose;
};

/**
 * Parse a single option.
 */
error_t parse_opt( int key, char *arg, struct argp_state *state );

static struct argp argp = {
  options, parse_opt, doc_args, doc_program, NULL, NULL, NULL };

/**
 * Sets structure elements to default values.
 */
void options_init( struct arguments *arguments );

#endif

