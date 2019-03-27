#ifndef H_FRACTAL_COLOURS
#define H_FRACTAL_COLOURS

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "algebra.h"
#include "logging.h"
#include "memory.h"

/**
 * Represents the hue, saturation, and value for a colour.
 */
typedef struct colour {
  /** Hue (0 to 360) */
  double h;
  /** Saturation (0 to 1) */
  double s;
  /** Value (0 to 1) */
  double v;
} colour;

/**
 * Returns the lowest value of the given parameters.
 *
 * @param a Compared against b.
 * @param b Compared against a.
 *
 * @return The smallest value of {a, b}.
 */
#define min( a, b ) colour_min( a, b, DBL_MAX )

/**
 * Returns the lowest value of the given parameters.
 *
 * @param a Compared against b and c.
 * @param b Compared against a and c.
 * @param c Compared against a and b.
 *
 * @return The smallest value of {a, b, c}.
 */
double colour_min( double a, double b, double c );

/**
 * Allocates memory for a colour structure and initialises it to a default
 * value.
 *
 * @return Memory allocated for a colour structure.
 */
colour *colour_open( void );

/**
 * Releases memory allocated to a colour structure.
 *
 * @param colour The reference to deallocate.
 */
void colour_close( colour *colour );

/**
 * Parses a colour string into its equivalent colour. The string f takes the
 * form `hsv(h,s,v)` where:
 *
 * - `hsv` is the function
 * - `h` is the hue (0 to 360)
 * - `s` is the saturation (0 to 1)
 * - `v` is the value (0 to 1)
 *
 * @param f Function string to parse.
 * @param colour Values from f are set into this structure.
 */
void colour_parse( char *f, colour *colour );

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

/**
 * Convert RGB to HSV.
 *
 * @param red Colour (0 to 255).
 * @param green Colour (0 to 255).
 * @param blue Colour (0 to 255).
 *
 * @param h Output Hue between 0 and 360
 * @param s Output saturation between 0 and 1
 * @param v Output value between 0 and 1
 *
 * @see https://en.wikipedia.org/wiki/HSL_and_HSV
 */
void colour_rgb_to_hsv(
  int red, int green, int blue, double *h, double *s, double *v );

#endif

