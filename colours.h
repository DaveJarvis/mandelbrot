#ifndef H_FRACTAL_COLOURS
#define H_FRACTAL_COLOURS

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define COLOUR_HUE_EDGE_LEN (65537L)

/**
 * Returns the lowest value of the given parameters.
 */
double colour_min( double a, double b, double c );

/**
 * Help convert HSV colour space to RGB colour space.
 */
double colour_frgb( double n, double h, double s, double v );

/**
 * Convert HSV to RGB.
 *
 * @param h Hue between 0 and 360
 * @param s Saturation between 0 and 1
 * @param v Value between 0 and 1
 *
 * @param r Output red colour (0 to 1).
 * @param g Output green colour (0 to 1).
 * @param b Output blue colour (0 to 1).
 *
 * @see https://en.wikipedia.org/wiki/HSL_and_HSV
 */
void colour_hsv_to_rgb(
  double h, double s, double v, double *r, double *g, double *b );

#endif

