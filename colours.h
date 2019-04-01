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
 * Represents the hue, saturation, and value for a colour, as well as its
 * RGB values.
 */
typedef struct colour {
  /** Hue (0 to 360), saturation (0 to 1), and value (0 to 1). */
  double hsv[3];

  /** Red (0 to 255), green (0 to 255), and blue (0 to 255). */
  double rgb[3];
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
 * form `hsv(h,s,v)` or `rgb(r,g,b)` where:
 *
 * - `f` is the colour function to parse.
 * - `h` is the hue (0 to 360) or red (0 to 255).
 * - `s` is the saturation (0 to 1) or green (0 to 255).
 * - `v` is the value (0 to 1) or blue (0 to 255).
 *
 * @param f Function string to parse.
 * @param out Values from f are set into this structure.
 */
void colour_parse( char *f, colour *out );

/**
 * Convert HSV to RGB.
 *
 * @param in.hsv[0] Hue between 0 and 360.
 * @param in.hsv[1] Saturation between 0 and 1.
 * @param in.hsv[2] Value between 0 and 1.
 *
 * @param out.rgb[0] Output red colour (0 to 1).
 * @param out.rgb[1] Output green colour (0 to 1).
 * @param out.rgb[2] Output blue colour (0 to 1).
 *
 * @see https://en.wikipedia.org/wiki/HSL_and_HSV
 */
void colour_hsv_to_rgb( colour *in, colour *out );

/**
 * Convert RGB to HSV.
 *
 * @param in.rgb[0] Red colour (0 to 255).
 * @param in.rgb[1] Green colour (0 to 255).
 * @param in.rgb[2] Blue colour (0 to 255).
 *
 * @param out.hsv[0] Output Hue between 0 and 360.
 * @param out.hsv[1] Output saturation between 0 and 1.
 * @param out.hsv[2] Output value between 0 and 1.
 *
 * @see https://en.wikipedia.org/wiki/HSL_and_HSV
 */
void colour_rgb_to_hsv( colour *in, colour *out );

#endif

