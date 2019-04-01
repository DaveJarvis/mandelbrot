#include "colours.h"

static const char *COLOUR_FUNC_HSV = "hsv";
static const char *COLOUR_FUNC_RGB = "rgb";

double colour_min( double a, double b, double c ) {
  return a < b
    ? (a < c ? a : c)
    : (b < c ? b : c);
}

colour *colour_open( void ) {
  return memory_open( (size_t)sizeof( colour ) );
}

void colour_close( colour *colour ) {
  memory_close( colour );
}

void colour_parse( char *f, colour *out ) {
  char name[3];
  double v1;
  double v2;
  double v3;

  // e.g., rgb(0,255,128)
  sscanf( f, "%3s(%lf,%lf,%lf)", name, &v1, &v2, &v3 );

  // The fractal rendering expects colours in HSV format.
  if( strncmp( (const char *)name, COLOUR_FUNC_HSV, 3 ) == 0 ) {
    out->hsv[0] = v1;
    out->hsv[1] = v2;
    out->hsv[2] = v3;
  }
  else if( strncmp( (const char *)name, COLOUR_FUNC_RGB, 3 ) == 0 ) {
    // The user can provide an RGB format, which are first converted to HSV.
    out->rgb[0] = v1;
    out->rgb[1] = v1;
    out->rgb[2] = v1;
    colour_rgb_to_hsv( out, out );
  }
}

void colour_hsv_to_rgb( colour *in, colour *out ) {
  double h = in->hsv[0];
  double s = in->hsv[1];
  double v = in->hsv[2];

  double *r = &(out->rgb[0]);
  double *g = &(out->rgb[1]);
  double *b = &(out->rgb[2]);

  if( s <= 0.0 ) {
    *r = v;
    *g = v;
    *b = v;
  }
  else {
    double hh = h >= 360.0 ? 0.0 : h / 60.0;
    long i = (long)hh;
    double ff = hh - i;
    double p = v * (1.0 - s);
    double q = v * (1.0 - (s * ff));
    double t = v * (1.0 - (s * (1.0 - ff)));

    switch( i ) {
      case  0: *r = v; *g = t; *b = p; break;
      case  1: *r = q; *g = v; *b = p; break;
      case  2: *r = p; *g = v; *b = t; break;
      case  3: *r = p; *g = q; *b = v; break;
      case  4: *r = t; *g = p; *b = v; break;
      case  5:
      default: *r = v; *g = p; *b = q; break;
    }
  }
}

void colour_rgb_to_hsv( colour *in, colour *out ) {
  double r = in->rgb[0] / 255.0;
  double g = in->rgb[1] / 255.0;
  double b = in->rgb[2] / 255.0;

  float k = 0.0;

  if( g < b ) {
    double t = g; g = b; b = t;
    k = -1.0;
  }

  if( r < g ) {
    double t = r; r = g; g = t;
    k = -2.0 / 6.0 - k;
  }

  float chroma = r - min( g, b );
  out->hsv[0] = fabs( k + (g - b) / (6.0 * chroma + 1e-20f) ) * 360;
  out->hsv[1] = chroma / (r + 1e-20f);
  out->hsv[2] = r;
}

