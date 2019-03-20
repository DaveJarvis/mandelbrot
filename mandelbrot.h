#ifndef __H_MANDELBROT
#define __H_MANDELBROT

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "errors.h"
#include "image.h"
#include "logging.h"
#include "memory.h"
#include "options.h"
#include "threads.h"

typedef struct mandelbrot_parameters {
  struct arguments *arguments;
  struct region *region;
  int **plot;

  Image image;
} mandelbrot_parameters;

/**
 * Allocates enough memory to hold parameters for each distinct thread.
 */
mandelbrot_parameters *mandelbrot_parameters_open();

/**
 * Called to release memory allocated from thread_parameters_open.
 */
void mandelbrot_parameters_close( mandelbrot_parameters *parameters );

/**
 * Called to allocate memory for storing histogram of interation values.
 */
int **mandelbrot_plot_open( struct arguments *args );

/**
 * Called to deallocate memory of interation values.
 */
void mandelbrot_plot_close( int **plot );

/**
 * Returns the number of iterations before iterating escapes the Mandelbrot
 * Set.
 */
int mandelbrot_escape( double complex c, int power, int max_iterate );

/**
 * Run by a single thread to fill in part of a Mandelbrot Set image.
 *
 * @param params The mandelbrot_parameters structure.
 */
void *mandelbrot_compute( void *params );

/**
 * Non-linear function to smooth the iteration values.
 */
double mandelbrot_nonlinear( int iterations, struct arguments *args );

/**
 * Render the image using the plotted data.
 *
 * @param plot The data computed from mandelbrot_compute.
 * @param args Command line arguments to configure settings.
 */
void mandelbrot_render( int **plot, Image image, struct arguments *args );

#endif

