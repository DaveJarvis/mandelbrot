#include "colours.h"

int colour_normalise( int iterations ) {
  return 0;
}

void colour_rgb_to_hsv(
  float r, float g, float b, float *h, float *s, float *v ) {
  float k = 0.f;

  if( g < b ) {
    /** Swap */
    float t = g; g = b; b = t;

    k = -1.f;
  }

  if( r < g ) {
    /** Swap */
    float t = g; g = r; r = t;

    k = -2.f / 6.f - k;
  }

  float chroma = r - min( g, b );
  *h = fabs( k + (g - b) / (6.f * chroma + 1e-20f) );
  *s = chroma / (r + 1e-20f);
  *v = r;
}

void colour_hsv_to_rgb(
  float h, float s, float v, float *r, float *g, float *b ) {
	if( s == 0 ) {
		*r = v;
		*g = v;
		*b = v;
	}
	else {
		int i;
		double f, p, q, t;

		if( h == 360 ) {
			h = 0;
    }
		else {
			h /= 60;
    }

		i = (int)trunc( h );
		f = h - i;

		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch( i ) {
      case  0: *r = v; *g = t; *b = p; break;
      case  1: *r = q; *g = v; *b = p; break;
      case  2: *r = p; *g = v; *b = t; break;
      case  3: *r = p; *g = q; *b = v; break;
      case  4: *r = t; *g = p; *b = v; break;
      default: *r = v; *g = p; *b = q; break;
		}
	}

	*r *= 255;
	*g *= 255;
	*b *= 255;
}

