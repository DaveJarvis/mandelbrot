#include "colours.h"

double colour_min( double a, double b, double c ) {
  return a < b
    ? (a < c ? a : c)
    : (b < c ? b : c);
}

double colour_normalise( double iterations ) {
  return iterations;
}

double colour_frgb( double n, double h, double s, double v ) {
  double k = (int)(n + h / 60.0) % 6;
  return v - v * s * fmax( colour_min( k, 4 - k, 1 ), 0 );
}

void colour_hsv_to_rgb(
  double h, double s, double v, double *r, double *g, double *b ) {
  *r = colour_frgb( 5, h, s, v );
  *g = colour_frgb( 3, h, s, v );
  *b = colour_frgb( 1, h, s, v );
}

