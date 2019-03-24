#include "fractal.h"

fractal_parameters *fractal_parameters_open( void ) {
  return memory_open( (size_t)sizeof( fractal_parameters ) );
}

void fractal_parameters_init(
  fractal_parameters *fractal, global_args *args ) {
  fractal->width = args->width;
  fractal->height = args->height;
  fractal->iterations = args->iterations;
  fractal->samples = args->samples;

  fractal->cx = args->cx;
  fractal->cy = args->cy;
  fractal->zoom = args->zoom;

  fractal->region = NULL;
  fractal->image = NULL;
  fractal->colour_base = NULL;

  random_init( fractal->random_state );
}

void fractal_parameters_validate( fractal_parameters *fractal ) {
  if( fractal->width < 1 ) {
    fractal->width = ARG_DEFAULT_WIDTH;
  }

  if( fractal->height < 1 ) {
    fractal->height = ARG_DEFAULT_HEIGHT;
  }

  if( fractal->iterations < 1 ) {
    fractal->iterations = ARG_DEFAULT_ITERATIONS;
  }

  if( fractal->samples < 1 ) {
    fractal->samples = ARG_DEFAULT_SAMPLES;
  }

  if( fractal->zoom < 1 ) {
    fractal->samples = ARG_DEFAULT_ZOOM;
  }
}

void fractal_parameters_copy(
  fractal_parameters *src, fractal_parameters *dst ) {
  dst->width = src->width;
  dst->height = src->height;
  dst->iterations = src->iterations;
  dst->samples = src->samples;

  dst->cx = src->cx;
  dst->cy = src->cy;
  dst->zoom = src->zoom;

  dst->image = src->image;
  dst->colour_base = src->colour_base;
}

void fractal_parameters_close( fractal_parameters *fractal ) {
  memory_close( fractal );
}

/*
double fractal_escape( double complex c, int power, int max_iterate ) {
  const double B = 256.0;

  double complex z = 0;
  int i = 0;

  while( i++ < max_iterate && cdot( z, z ) < (B * B) ) {
    z = cpow( z, power ) + c;
  }

  return i - log2( log2( cdot( z, z ) ) ) + 4.0;
}

double fractal_escape( double complex c, int power, int max_iterate ) {
  const double light_height = 1.5;
  const double light_angle = 45;
  double complex v = cexp( 2.0 * light_angle * M_PI * (_Complex double)I );

  // Escape boundary
  const long B = 1000;

  double complex z = c;

  // Derivative of c
  double complex dC = 1.0 * (_Complex double)I;

  // Squared derivative of c
  double complex dC2 = 0.0 * (_Complex double)I;

  double colour = 0.0;

  for( int i = 0; i < max_iterate; i++ ) {
    if( fractal_inside( c ) ) {
      break;
    }

    if( cabs( z ) > B * B ) {
      double lo = 0.5 * log( cabs( z ) );

      double complex u =
        z * dC * ((1 + lo) * conj( cpow( dC, 2 ) ) - lo * conj( z * dC2 ));
      u = u / cabs( u );

      colour = cdot( u, v ) + light_height;
      colour = colour / (1.0 + light_height);

      break;
    }

    double complex nz = cpow( z, power ) + c;
    double complex ndC = 2 * dC * z + 1;
    double complex ndC2 = 2 * (dC2 * z + cpow( dC, 2 ));
    z = nz;
    dC = ndC;
    dC2 = ndC2;
  }

  return colour;
}
*/

bool fractal_inside( double complex c ) {
  double absc = cabs( c );

  double cardioid =
    256 * pow( absc, 4 ) -
    96 * pow( absc, 2 ) +
    32 * creal( c ) - 3;

  double bulb = 4 * pow( cabs( c + 1 ), 2 ) - 0.25;

  return cardioid < 0 || bulb < 0;
}

double fractal_distance( UNUSED int i, double complex z, double complex dC ) {
  const double light_height = 1.5;
  const double light_angle = 45;
  double complex v = cexp( 2.0 * light_angle * M_PI * (_Complex double)I );

  double complex u = z / dC;
  u = u / cabs( u );

  double normal = cdot( u, v ) + light_height;
  return normal / (1.0 + light_height);
}

double fractal_escape( double complex c, int power, int max_iterate ) {
  // Escape boundary
  const long B = 1000;

  // Derivative of c
  double complex dC = 0.0;
  double complex z = 0.0;

  double colour = 0.0;

  for( int i = 0; i < max_iterate; i++ ) {
    dC = 2.0 * dC * z + 1.0;
    z = cpow( z, power ) + c;

    if( fractal_inside( c ) ) {
      break;
    }

    if( cabs( z ) > B * B ) {
      colour = fractal_distance( i, z, dC );
      break;
    }
  }

  return colour;
}

void *fractal_compute( void *f ) {
  fractal_parameters *fractal = f;
  struct region *region = fractal->region;

  int i = fractal->iterations;
  int s = fractal->samples;
  double z = 1 / fractal->zoom;
  uint32_t *state = fractal->random_state;

  double r = 0;
  double g = 0;
  double b = 0;

  log_debug( "Translate coordinates to complex plane" );
  double x_real = region->x1 * z - fractal->width / 2.0 * z + fractal->cx;
  double y_start = region->y1 * z - fractal->height / 2.0 * z + fractal->cy;

  // Area boundaries for sampling relative to real/imaginary coordinate.
  unsigned int ssize = (unsigned int)(round( sqrt( s ) )) + 1;

  log_debug( "Compute escape values for region" );
  for( int x = region->x1; x < region->x2; x++, x_real += z ) {
    double y_imag = y_start;

    for( int y = region->y1; y < region->y2; y++, y_imag += z ) {
      // Create complex variable c for Mandelbrot Set equation z = z^2 + c
      double complex c = x_real + y_imag * (_Complex double)I;

      // Compute the iterations (colour) from the escape.
      double distance = fractal_escape( c, 2, i );
      fractal_colour( fractal->colour_base, distance, &r, &g, &b );

      // If antialiasing was requested...
      if( s > 1 ) {
        double rr = r;
        double rg = g;
        double rb = b;

        // Average neighbouring pixels picked at random.
        for( int p = 0; p < s; p++ ) {
          double xsign = random_next( state ) % 2 ? 1 : -1;
          double ysign = random_next( state ) % 2 ? 1 : -1;

          double rx = x_real + ((random_next( state ) % ssize) * z / s) * xsign;
          double ry = y_imag + ((random_next( state ) % ssize) * z / s) * ysign;

          double complex rc = rx + ry * (_Complex double)I;
          double tr = 0;
          double tg = 0;
          double tb = 0;

          double rdistance = fractal_escape( rc, 2, i );
          fractal_colour( fractal->colour_base, rdistance, &tr, &tg, &tb );
          rr += tr;
          rg += tg;
          rb += tb;
        }

        r = rr / (s + 1);
        g = rg / (s + 1);
        b = rb / (s + 1);
      }

      image_pixel( fractal->image, x, y,
        (int)(r * 255), (int)(g * 255), (int)(b * 255) );
    }
  }

  pthread_exit( NULL );
}

void fractal_colour( colour *colour_base,
  double plotted, double *r, double *g, double *b ) {
  double h = 0.0;
  double s = 0.0;
  double v = plotted;

  if( v <= 0 ) {
    h = colour_base->h;
    s = colour_base->s;
    v = colour_base->v;
  }

  colour_hsv_to_rgb( h, s, v, r, g, b );
}

