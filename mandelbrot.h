#ifndef __H_MANDELBROT
#define __H_MANDELBROT

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Returns the number of iterations before z_n+1_ = z^2 + c iterated past 2.
 *
 * @param c A complex number.
 * @param max_iterate Maximum times to iterate.
 */
int m( double complex c, int max_iterate );

#endif

