#ifndef __H_COLOURS
#define __H_COLOURS

#include <math.h>

/**
 * https://stackoverflow.com/a/3437484/59087
 */
#define min(a,b) \
 ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
   _a < _b ? _a : _b; })

/**
 * Stretches the colours by mapping the number of iterations to a colour.
 */
int colour_normalise( int iterations );

/**
 * Convert RGB to HSV.
 *
 * From http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
 */
void colour_rgb_to_hsv(
  float r, float g, float b,
  float *h, float *s, float *v );

/**
 * Convert HSV to RGB.
 *
 * @param h Hue between 0 and 1
 * @param s Saturation between 0 and 1
 * @param v Value between 0 and 1
 *
 * @return r, g, b valued between 0 and 255.
 */
void colour_hsv_to_rgb(
  float h, float s, float v,
  float *r, float *g, float *b );

#endif

