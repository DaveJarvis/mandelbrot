#include "mandelbrot.h"

mandelbrot_parameters *mandelbrot_parameters_open( void ) {
  mandelbrot_parameters *parameters =
    memory_open( (size_t)sizeof( mandelbrot_parameters ) );

  if( parameters != NULL ) {
    parameters->arguments = NULL;
    parameters->region = NULL;
    parameters->image = NULL;
    parameters->plot = NULL;
  }

  return parameters;
}

void mandelbrot_parameters_close( mandelbrot_parameters *parameters ) {
  if( parameters != NULL ) {
    memory_close( parameters );
  }
}

plot_t **mandelbrot_plot_open( struct arguments *args ) {
  int width = args->width;
  int height = args->height;

  plot_t **plot = memory_open(
    (size_t)sizeof( plot_t * ) * (size_t)width );
  plot[0] = memory_open(
    (size_t)sizeof( plot_t ) * (size_t)width * (size_t)height );

  // Adjust the memory offsets
  for( int i = 0; i < width; i++ ) {
    plot[ i ] = (*plot + height * i);
  }

  return plot;
}

void mandelbrot_plot_close( plot_t **plot ) {
  memory_close( plot );
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

plot_t mandelbrot_escape( double complex c, int power, int max_iterate ) {
  const double light_height = 1.5;
  const double light_angle = 45;
  double complex v = cexp( 2.0 * light_angle * M_PI * (_Complex double)I );

  // Escape boundary
  const int B = 1000;

  double complex z = 0.0;
  double complex dC = 0.0;

  double colour = 0.0;

  for( int i = 0; i < max_iterate; i++ ) {
    dC = 2.0 * dC * z + 1.0;
    z = cpow( z, power ) + c;

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

void *mandelbrot_compute( void *params ) {
  mandelbrot_parameters *parameters = params;
  struct arguments *args = parameters->arguments;
  struct region *region = parameters->region;
  plot_t **plot = parameters->plot;

  int w = args->width;
  int h = args->height;
  int i = args->iterations;
  double zoom = 1 / args->zoom;

  // Translate Cartesian x coordinate to the complex plane.
  double x_real = region->x1 * zoom - w / 2.0 * zoom + args->cx;
  double y_start = region->y1 * zoom - h / 2.0 * zoom + args->cy;

  // Iterate over a region; store the Mandelbrot Set escape value per pixel.
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

void mandelbrot_paint( plot_t **plot, Image image, struct arguments *args ) {
  double max_iterations = args->iterations;

  for( int x = 0; x < args->width; x++ ) {
    for( int y = 0; y < args->height; y++ ) {
      plot_t iterations = plot[x][y];

      log_verbose( args, "(%03d, %03d) = %f", x, y, iterations );

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

