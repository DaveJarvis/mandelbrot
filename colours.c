#include "algebra.h"
#include "colours.h"

double colour_min( double a, double b, double c ) {
  return a < b
    ? (a < c ? a : c)
    : (b < c ? b : c);
}

colour *colour_open( void ) {
  colour *colour = memory_open( (size_t)sizeof( colour ) );

  if( colour != NULL ) {
    colour_parse( DEFAULT_COLOUR_BASE, colour );
  }

  return colour;
}

void colour_close( colour *colour ) {
  memory_close( colour );
}

void colour_parse( char *f, colour *colour ) {
  const char *hsv = "hsv";
  char name[3];
  double v1;
  double v2;
  double v3;

  sscanf( f, "%3s(%lf,%lf,%lf)", name, &v1, &v2, &v3 );

  if( strstr( (const char *)name, hsv ) ) {
    colour->h = v1;
    colour->s = v2;
    colour->v = v3;
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

