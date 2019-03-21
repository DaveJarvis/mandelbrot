#ifndef __H_COLOURS
#define __H_COLOURS

#include <math.h>

#include "algebra.h"

/**
 * Returns the lowest value of the given parameters.
 */
double colour_min( double a, double b, double c );

/**
 * Stretches the colours by mapping the number of iterations to a colour.
 */
int colour_normalise( int iterations );

/**
 * Convert RGB to HSV.
 */
void colour_rgb_to_hsv(
  int r, int g, int b, double *h, double *s, double *v );

/**
 * Help convert HSV colour space to RGB colour space.
 */
double colour_convert( double n, double h, double s, double v );

/**
 * Convert HSV to RGB.
 *
 * @param h Hue between 0 and 360
 * @param s Saturation between 0 and 1
 * @param v Value between 0 and 1
 *
 * @return r, g, b valued between 0 and 1.
 *
 * @see https://en.wikipedia.org/wiki/HSL_and_HSV
 */
void colour_hsv_to_rgb(
  double h, double s, double v, double *r, double *g, double *b );

#endif

