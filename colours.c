#include "colours.h"

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

void colour_hsv_to_rgb(
  double h, double s, double v, double *r, double *g, double *b ) {
  h = ((int)h % 360) / 60.0;

  int i = (int)floor( h );
  double f = h - i;

  double p = v * (1.0 - s);
  double q = v * (1.0 - (s * f));
  double t = v * (1.0 - (s * (1.0 - f)));

  switch( i ) {
    case  0: *r = v; *g = t; *b = p; break;
    case  1: *r = q; *g = v; *b = p; break;
    case  2: *r = p; *g = v; *b = t; break;
    case  3: *r = p; *g = q; *b = v; break;
    case  4: *r = t; *g = p; *b = v; break;
    default: *r = v; *g = p; *b = q; break;
  }
}

