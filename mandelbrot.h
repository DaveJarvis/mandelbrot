#ifndef H_MANDELBROT_MANDELBROT
#define H_MANDELBROT_MANDELBROT

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "algebra.h"
#include "errors.h"
#include "image.h"
#include "logging.h"
#include "memory.h"
#include "threads.h"

#define DEFAULT_IMAGE_WIDTH 1024
#define DEFAULT_IMAGE_HEIGHT 768
#define DEFAULT_ITERATIONS 50
#define DEFAULT_SAMPLES 1

#define DEFAULT_PLOT_X    -0.75
#define DEFAULT_PLOT_Y     0.00
#define DEFAULT_PLOT_ZOOM  300

typedef double plot_t;

typedef struct mandelbrot_parameters {
  int width, height;
  int iterations, samples;
  double cx, cy, zoom;

  struct region *region;
  plot_t **plot;

  Image image;
} mandelbrot_parameters;

/**
 * Allocates enough memory to hold parameters for each distinct thread.
 */
mandelbrot_parameters *mandelbrot_parameters_open( void );

/**
 * Initializes memory for the fractal parameters.
 */
void mandelbrot_parameters_init( mandelbrot_parameters *fractal );

/**
 * Initializes the destination parameters using the source parameters.
 */
void mandelbrot_parameters_copy(
  mandelbrot_parameters *src, mandelbrot_parameters *dst );

/**
 * Called to release memory allocated from thread_parameters_open.
 */
void mandelbrot_parameters_close( mandelbrot_parameters *fractal );

/**
 * Called to allocate memory for storing histogram of interation values.
 */
void mandelbrot_plot_open( mandelbrot_parameters *fractal );

/**
 * Called to deallocate memory of interation values.
 */
void mandelbrot_plot_close( mandelbrot_parameters *fractal );

/**
 * Determines whether the given point is within either the main cardioid or
 * period-2 bulb.
 *
 * @param c The point on the complex plane to test.
 * @return true The given point iterates to infinity.
 *
 * @see https://en.wikipedia.org/wiki/Mandelbrot_set
 * @see http://iquilezles.untergrund.net/www/articles/msets/msets.pdf
 */
bool mandelbrot_inside( double complex c );

/**
 * Returns a smoothed value representing the number of iterations before
 * exiting from the iteration (to infinity).
 *
 * @return A number to use for colouring or 0.0 if iterated to infinity.
 */
plot_t mandelbrot_escape( double complex c, int power, int max_iterate );

/**
 * Run by a single thread to fill in part of a Mandelbrot Set image.
 *
 * @param f The mandelbrot_parameters fractal controls.
 */
void *mandelbrot_compute( void *f );

/**
 * Paint the image using the plotted data.
 */
void mandelbrot_paint( mandelbrot_parameters *fractal );

#endif

