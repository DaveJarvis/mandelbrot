#include "colours.h"
#include "mandelbrot.h"

mandelbrot_parameters *mandelbrot_parameters_open( void ) {
  mandelbrot_parameters *fractal =
    memory_open( (size_t)sizeof( mandelbrot_parameters ) );

  if( fractal != NULL ) {
    mandelbrot_parameters_init( fractal );
  }

  return fractal;
}

void mandelbrot_parameters_init( mandelbrot_parameters *fractal ) {
  fractal->width = DEFAULT_IMAGE_WIDTH;
  fractal->height = DEFAULT_IMAGE_HEIGHT;
  fractal->iterations = DEFAULT_ITERATIONS;
  fractal->samples = DEFAULT_SAMPLES;

  fractal->cx = DEFAULT_PLOT_X;
  fractal->cy = DEFAULT_PLOT_Y;
  fractal->zoom = DEFAULT_PLOT_ZOOM;

  fractal->region = NULL;
  fractal->plot = NULL;
  fractal->image = NULL;
}

void mandelbrot_parameters_copy(
  mandelbrot_parameters *src, mandelbrot_parameters *dst ) {
  dst->width = src->width;
  dst->height = src->height;
  dst->iterations = src->iterations;
  dst->samples = src->samples;

  dst->cx = src->cx;
  dst->cy = src->cy;
  dst->zoom = src->zoom;

  dst->plot = src->plot;
  dst->image = src->image;
}

void mandelbrot_parameters_close( mandelbrot_parameters *fractal ) {
  memory_close( fractal );
}

void mandelbrot_plot_open( mandelbrot_parameters *fractal ) {
  int width = fractal->width;
  int height = fractal->height;

  plot_t **plot = memory_open(
    (size_t)sizeof( plot_t * ) * (size_t)width );

  if( plot != NULL ) {
    plot[0] = memory_open(
      (size_t)sizeof( plot_t ) * (size_t)width * (size_t)height );

    if( plot[0] == NULL ) {
      memory_close( plot );
    }
    else {
      // Adjust the memory offsets
      for( int i = 0; i < width; i++ ) {
        plot[ i ] = (*plot + height * i);
      }
    }
  }

  fractal->plot = plot;
}

void mandelbrot_plot_close( mandelbrot_parameters *fractal ) {
  memory_close( fractal->plot );
}

/*
plot_t mandelbrot_escape( double complex c, int power, int max_iterate ) {
  const double B = 256.0;

  double complex z = 0;
  int i = 0;

  while( i++ < max_iterate && cdot( z, z ) < (B * B) ) {
    z = cpow( z, power ) + c;
  }

  return i - log2( log2( cdot( z, z ) ) ) + 4.0;
}
*/

bool mandelbrot_inside( double complex c ) {
  double absc = cabs( c );

  double cardioid =
    256 * pow( absc, 4 ) -
    96 * pow( absc, 2 ) +
    32 * creal( c ) - 3;

  double bulb = 4 * pow( cabs( c + 1 ), 2 ) - 0.25;

  return cardioid < 0 || bulb < 0;
}

plot_t mandelbrot_escape( double complex c, int power, int max_iterate ) {
  const double light_height = 1.5;
  const double light_angle = 45;
  double complex v = cexp( 2.0 * light_angle * M_PI * (_Complex double)I );

  // Escape boundary
  const long B = 1000;

  // Derivative of c
  double complex dC = 0.0;
  double complex z = 0.0;

  double colour = 0.0;

  for( int i = 0; i < max_iterate; i++ ) {
    dC = 2.0 * dC * z + 1.0;
    z = cpow( z, power ) + c;

    if( mandelbrot_inside( c ) ) {
      break;
    }

    if( cabs( z ) > B * B ) {
      double complex u = z / dC;
      u = u / cabs( u );

      colour = cdot( u, v ) + light_height;
      colour = colour / (1.0 + light_height);

      break;
    }
  }

  return colour;
}

void *mandelbrot_compute( void *f ) {
  mandelbrot_parameters *fractal = f;
  struct region *region = fractal->region;
  plot_t **plot = fractal->plot;

  int w = fractal->width;
  int h = fractal->height;
  int i = fractal->iterations;
  double zoom = 1 / fractal->zoom;

  log_debug( "Translate coordinates to complex plane" );
  double x_real = region->x1 * zoom - w / 2.0 * zoom + fractal->cx;
  double y_start = region->y1 * zoom - h / 2.0 * zoom + fractal->cy;

  log_debug( "(%d, %d) - (%d, %d)",
    region->x1, region->y1, region->x2, region->y2 );
  log_debug( "(%f, %f) @ %f", fractal->cx, fractal->cy, fractal->zoom );

  log_debug( "Compute escape values for region" );
  for( int x = region->x1; x < region->x2; x++, x_real += zoom ) {
    double y_imag = y_start;

    for( int y = region->y1; y < region->y2; y++, y_imag += zoom ) {
      // Create complex variable c for Mandelbrot Set equation z = z^2 + c
      double complex c = x_real + y_imag * (_Complex double)I;

      // Compute the iterations (colour) from the escape.
      plot[x][y] = mandelbrot_escape( c, 2, i );
    }
  }

  pthread_exit( NULL );
}

void mandelbrot_paint( mandelbrot_parameters *fractal ) {
  plot_t **plot = fractal->plot;
  Image image = fractal->image;
  double max_iterations = fractal->iterations;

  for( int x = 0; x < fractal->width; x++ ) {
    for( int y = 0; y < fractal->height; y++ ) {
      plot_t iterations = plot[x][y];

      double h = 0.0;
      double s = 0.0;
      double v = iterations;

      if( v <= 0 ) {
        h = 215.7;
        s = 0.987;
        v = 0.294;
      }

      double r = 0;
      double g = 0;
      double b = 0;

      colour_hsv_to_rgb( h, s, v, &r, &g, &b );

      image_pixel( image, x, y,
        (int)(r * 255), (int)(g * 255), (int)(b * 255) );
    }
  }
}

