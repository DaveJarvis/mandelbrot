#include "colours.h"

double colour_min( double a, double b, double c ) {
  return a < b
    ? (a < c ? a : c)
    : (b < c ? b : c);
}

int colour_normalise( int iterations ) {
  return 0;
}

void colour_rgb_to_hsv(
  int r, int g, int b, double *h, double *s, double *v ) {
  double k = 0.f;

  if( g < b ) {
    /** Swap */
    double t = g; g = b; b = t;

    k = -1.f;
  }

  if( r < g ) {
    /** Swap */
    double t = g; g = r; r = t;

    k = -2.f / 6.f - k;
  }

  double chroma = r - min( g, b );
  *h = fabs( k + (g - b) / (6.f * chroma + 1e-20f) );
  *s = chroma / (r + 1e-20f);
  *v = r;
}

double colour_convert( double n, double h, double s, double v ) {
  double k = (int)(n + h / 60.0) % 6;
  return v - v * s * max( colour_min( k, 4 - k, 1 ), 0 );
}

void colour_hsv_to_rgb(
  double h, double s, double v, double *r, double *g, double *b ) {
  *r = colour_convert( 5, h, s, v );
  *g = colour_convert( 3, h, s, v );
  *b = colour_convert( 1, h, s, v );
}

