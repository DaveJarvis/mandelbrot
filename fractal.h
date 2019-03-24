#ifndef H_FRACTAL_MANDELBROT
#define H_FRACTAL_MANDELBROT

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "algebra.h"
#include "args.h"
#include "colours.h"
#include "errors.h"
#include "image.h"
#include "logging.h"
#include "memory.h"
#include "random.h"
#include "threads.h"

/**
 * Controls how the final image appears when rendered.
 */
typedef struct fractal_parameters {
  /** Canvas width in pixels. */
  int width;
  /** Canvas height in pixels. */
  int height;

  /** How many iterations to test for escaping to infinity. */
  int iterations;
  /** Number of neighbouring pixels to subsample. */
  int samples;

  /** Central x coordinate for fractal zoom. */
  double cx;
  /** Central y coordinate for fractal zoom. */
  double cy;
  /** Zoom into (cx, cy) by this amount. */
  double zoom;

  /** True colour canvas. */
  Image image;

  /** Area to draw; used by threads for embarassingly parallel work. */
  struct region *region;

  /** Colour of the Mandelbrot Set after parsing. */
  colour *colour_base;

  /** Used by the thread-safe random number generator. */
  uint32_t random_state[ RANDOM_STATE_SIZE ];
} fractal_parameters;

/**
 * Allocates enough memory to hold parameters for each distinct thread.
 */
fractal_parameters *fractal_parameters_open( void );

/**
 * Initializes memory for the fractal parameters.
 *
 * @param fractal The parameters used to configure the fractal.
 * @param args Post-parsed commmand line parameters.
 */
void fractal_parameters_init( fractal_parameters *fractal, global_args *args );

/**
 * Ensure that all command line parameters are set to valid values.
 */
void fractal_parameters_validate( fractal_parameters *fractal );

/**
 * Initializes the destination parameters using the source parameters.
 */
void fractal_parameters_copy(
  fractal_parameters *src, fractal_parameters *dst );

/**
 * Called to release memory allocated from thread_parameters_open.
 */
void fractal_parameters_close( fractal_parameters *fractal );

/**
 * Determines whether the given point is within either the main cardioid or
 * period-2 bulb.
 *
 * @param c The point on the complex plane to test.
 * @return true The given point iterates to infinity.
 *
 * @see https://en.wikipedia.org/wiki/fractal_set
 * @see http://iquilezles.untergrund.net/www/articles/msets/msets.pdf
 */
bool fractal_inside( double complex c );

/**
 * Generates a distance for the given iteration, escape parameter, and 
 * derivative.
 *
 * @param i The iteration number up to max iterations.
 * @param z The complex number that may (or may not) iterate to infinity.
 * @param dC The derivative of c, the complex plane coordinate.
 *
 * @return A value used to pick a colour for the painting, or 0 for values
 * that iterate to infinity.
 */
double fractal_distance( int i, double complex z, double complex dC );

/**
 * Returns a smoothed value representing the number of iterations before
 * exiting from the iteration (to infinity).
 *
 * @return A number to use for colouring or 0.0 if iterated to infinity.
 */
double fractal_escape( double complex c, int power, int max_iterate );

/**
 * Run by a single thread to fill in part of a Mandelbrot Set image.
 *
 * @param f The fractal_parameters fractal controls.
 */
void *fractal_compute( void *f );

/**
 * Generate a colour for a point on the fractal plot.
 *
 * @param plotted Value returned from fractal_distance.
 * @param r Returns red channel between 0 and 1.
 * @param g Returns green channel between 0 and 1.
 * @param b Returns blue channel between 0 and 1.
 */
void fractal_colour( colour *base,
  double plotted, double *r, double *g, double *b );

/**
 * Paint the image using the plotted data.
 */
void fractal_paint( fractal_parameters *fractal );

#endif

