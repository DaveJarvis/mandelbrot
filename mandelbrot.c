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

  plot_t **plot = memory_open( (size_t)sizeof( plot_t * ) * (size_t)width );
  plot[0] = memory_open( (size_t)sizeof( plot_t ) * (size_t)width * (size_t)height );

  // Adjust the memory offsets
  for( int i = 0; i < width; i++ ) {
    plot[ i ] = (*plot + height * i);
  }

  return plot;
}

void mandelbrot_plot_close( plot_t **plot ) {
  memory_close( plot );
}

plot_t mandelbrot_escape( double complex c, int power, int max_iterate ) {
  const double B = 256.0;

  double complex z = 0;
  int i = 0;

  while( i++ < max_iterate && cdot( z, z ) < (B * B) ) {
    z = cpow( z, power ) + c;
  }

  return i - log2( log2( cdot( z, z ) ) ) + 4.0;
}

void *mandelbrot_compute( void *params ) {
  mandelbrot_parameters *parameters = params;
  struct arguments *args = parameters->arguments;
  struct region *region = parameters->region;
  plot_t **plot = parameters->plot;

  int w = args->width;
  int h = args->height;
  int i = args->iterations;
  double x1 = args->plot_r1;
  double x2 = args->plot_r2;
  double y1 = args->plot_i1;
  double y2 = args->plot_i2;

  for( int x = region->x1; x < region->x2; x++ ) {
    for( int y = region->y1; y < region->y2; y++ ) {
      double x_real = x1 + (x * 1.0 / w) * (x2 - x1);
      double y_imag = y1 + (y * 1.0 / h) * (y2 - y1);

      double complex c = x_real + y_imag * (_Complex double)I;

      plot[x][y] = mandelbrot_escape( c, 2, i );
    }
  }

  pthread_exit( NULL );
}

void mandelbrot_paint( plot_t **plot, Image image, struct arguments *args ) {
  int max_iterations = args->iterations;

  for( int x = 0; x < args->width; x++ ) {
    for( int y = 0; y < args->height; y++ ) {
      plot_t iterations = plot[x][y];

      log_verbose( args, "(%03d, %03d) = %f", x, y, iterations );

      double h = 0.0;
      double s = 1.0;
      double v = iterations / max_iterations;

      double r = 0;
      double g = 0;
      double b = 0;

      colour_hsv_to_rgb( h, s, v, &r, &g, &b );

      image_pixel( image, x, y, (int)(r * 255), (int)(g * 255), (int)(b * 255) );
    }
  }
}

