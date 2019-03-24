#include "algebra.h"
#include "colours.h"

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

void colour_parse( char *f, colour *colour ) {
  const char *hsv = "hsv";
  const char *rgb = "rgb";
  char name[3];
  double v1;
  double v2;
  double v3;

  sscanf( f, "%3s(%lf,%lf,%lf)", name, &v1, &v2, &v3 );

  if( strncmp( (const char *)name, hsv, 3 ) == 0 ) {
    colour->h = v1;
    colour->s = v2;
    colour->v = v3;
  }
  else if( strncmp( (const char *)name, rgb, 3 ) == 0 ) {
    colour_rgb_to_hsv(
      v1, v2, v3, &(colour->h), &(colour->s), &(colour->v) );
  }
}

void colour_hsv_to_rgb(
  double h, double s, double v, double *r, double *g, double *b ) {

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

void colour_rgb_to_hsv(
  int red, int green, int blue, double *h, double *s, double *v ) {

  double r = red / 255.0;
  double g = green / 255.0;
  double b = blue / 255.0;

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
  *h = fabs( k + (g - b) / (6.0 * chroma + 1e-20f) ) * 360;
  *s = chroma / (r + 1e-20f);
  *v = r;
}

