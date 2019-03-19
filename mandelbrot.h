#ifndef __H_MANDELBROT
#define __H_MANDELBROT

#include <stdio.h>
#include <stdbool.h>
#include <complex.h>

#define ITERATION_X (0.05)
#define ITERATION_Y (0.05)

/**
 * Returns z^2 + c.
 *
 * @param z A complex number.
 * @param c A complex number.
 * @param iter Number of iterations.
 */
double complex f( double complex z, double complex c, int iter );

#endif

