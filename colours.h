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
 * Maps the number of iterations to a colour.
 */
int colour_normalise( int iterations );

/**
 * Convert RGB to HSV.
 */
void colour_rgb_to_hsv(
  float r, float g, float b,
  float *h, float *s, float *v );

/**
 * Convert HSV to RGB.
 */
void colour_hsv_to_rgb(
  float h, float s, float v,
  float *r, float *g, float *b );

#endif

