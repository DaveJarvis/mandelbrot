#include "algebra.h"
#include "colours.h"

double colour_min( double a, double b, double c ) {
  return a < b
    ? (a < c ? a : c)
    : (b < c ? b : c);
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

/*
void hsv2rgb(
  uint32_t h, uint16_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
  if (s == 0 || v == 0) {
    *r = v;
    *g = v;
    *b = v;
    return;
  }

  uint32_t delta = ((s * v) >> 16) + 1;
  uint8_t min = (uint8_t)(v - delta);
  uint8_t *mid;

  if (h >= COLOUR_HUE_EDGE_LEN * 4) {
    h -= COLOUR_HUE_EDGE_LEN * 4;

    if (h < COLOUR_HUE_EDGE_LEN) {
      *b = v;
      *g = min;
      mid = r;
    }
    else {
      h -= COLOUR_HUE_EDGE_LEN;
      h = COLOUR_HUE_EDGE_LEN - h;
      *r = v;
      *g = min;
      mid = b;
    }
  }
  else if (h >= COLOUR_HUE_EDGE_LEN * 2) {
    h -= COLOUR_HUE_EDGE_LEN * 2;

    if (h < COLOUR_HUE_EDGE_LEN) {
      *g = v;
      *r = min;
      mid = b;
    }
    else {
      h -= COLOUR_HUE_EDGE_LEN;
      h = COLOUR_HUE_EDGE_LEN - h;
      *b = v;
      *r = min;
      mid = g;
    }
  }
  else {
    if (h < COLOUR_HUE_EDGE_LEN) {
      *r = v;
      *b = min;
      mid = g;
    }
    else {
      h -= COLOUR_HUE_EDGE_LEN;
      h = COLOUR_HUE_EDGE_LEN - h;
      *g = v;
      *b = min;
      mid = r;
    }
  }

  *mid = ((h * delta) >> 16) + min;
}

void rgb2hsv(
  uint8_t r, uint8_t g, uint8_t b, uint32_t *h, uint16_t *s, uint8_t *v) {
  uint8_t max, mid, min;
  uint32_t edge;
  bool inverse;

  if (r > g) {
      if (g >= b) {
          max = r;
          mid = g;
          min = b;
          edge = 0;
          inverse = false;
      } else if (r > b) {
          max = r;
          mid = b;
          min = g;
          edge = 5;
          inverse = true;
      } else {
          max = b;
          mid = r;
          min = g;
          edge = 4;
          inverse = false;
      }
  } else if (r > b) {
      max = g;
      mid = r;
      min = b;
      edge = 1;
      inverse = true;
  } else {
      if (g > b) {
          max = g;
          mid = b;
          min = r;
          edge = 2;
          inverse = false;
      } else {
          max = b;
          mid = g;
          min = r;
          edge = 3;
          inverse = true;
      }
  }

  *v = max;

  uint32_t delta = max - min;
  if (delta == 0) {
      s = 0;
      h = 0;
      return;
  }

  *s = ((delta << 16) - 1) / *v;

  *h = (((mid - min) << 16) / delta) + 1;

  if (inverse) {
      *h = COLOUR_HUE_EDGE_LEN - *h;
  }

  *h += edge * COLOUR_HUE_EDGE_LEN;
}
*/

