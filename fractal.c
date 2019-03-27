#include "fractal.h"

fractal_parameters *fractal_parameters_open( void ) {
  return memory_open( (size_t)sizeof( fractal_parameters ) );
}

void fractal_parameters_init( fractal_parameters *fractal, global_args *args ) {
  // Assign the command-line parameters to the fractal controls.
  fractal->width = args->width;
  fractal->height = args->height;
  fractal->iterations = args->iterations;
  fractal->samples = args->samples;

  // Complex coordinate used for zooming into the fractal.
  fractal->cx = args->cx;
  fractal->cy = args->cy;
  fractal->zoom = args->zoom;

  // Initialized in main.
  fractal->region = NULL;
  fractal->image = NULL;
  fractal->colour_base = NULL;

  // Ensures thread-safety for random number generation, used by antialiasing.
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

  // Every thread needs its own copy of the fractal configuration options.
  dst->width = src->width;
  dst->height = src->height;
  dst->iterations = src->iterations;
  dst->samples = src->samples;

  // Central coordinates for zooming intot he fractal.
  dst->cx = src->cx;
  dst->cy = src->cy;
  dst->zoom = src->zoom;

  // Threads simultaneously write to this image.
  dst->image = src->image;
  dst->colour_base = src->colour_base;
}

void fractal_parameters_close( fractal_parameters *fractal ) {
  memory_close( fractal );
}

bool fractal_inside( double complex c ) {
  double absc = cabs( c );

  // Used to determine whether point is inside the Mandelbrot heart shape.
  double cardioid =
    256 * pow( absc, 4 ) -
    96 * pow( absc, 2 ) +
    32 * creal( c ) - 3;

  // Used to determine whether point is inside the largest Mandelbrot circle.
  double bulb = 16.0 * pow( cabs( c + 1 ), 2 ) - 1;

  return cardioid < 0 || bulb < 0;
}

double fractal_distance( UNUSED int i, double complex z, double complex dC ) {
  // Distance from "camera" to light source.
  const double light_height = 1.5;

  // Angle of light hitting the 2D surface.
  const double light_angle = 45;

  // Part of the normal calculation.
  double complex v = cexp( 2.0 * light_angle * M_PI * (_Complex double)I );

  double complex u = z / dC;
  u = u / cabs( u );

  // Determine the shading based on the surface normal.
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

  // Loop until it is determined that z will iterate to infinity (or maximum
  // iterations is met). This determines the boundary for the fractal's edge.
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

  // Allow the user to provide integer values as zoom parameters.
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

        // Determine antialiased colour by averaging randomly selected points.
        r = rr / (s + 1);
        g = rg / (s + 1);
        b = rb / (s + 1);
      }

      // Plot the pixel with or without antialiasing.
      image_pixel( fractal->image, x, y,
        (int)(r * 255), (int)(g * 255), (int)(b * 255) );
    }
  }

  pthread_exit( NULL );
}

void fractal_colour( colour *colour_base,
  double plotted, double *r, double *g, double *b ) {
  // Fractal distance is used to provide a shading to fake a heightmap.
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

