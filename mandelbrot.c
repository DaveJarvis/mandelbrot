#include "mandelbrot.h"

mandelbrot_parameters *mandelbrot_parameters_open() {
  mandelbrot_parameters *parameters =
    memory_open( sizeof( mandelbrot_parameters ) );

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

int **mandelbrot_plot_open( struct arguments *args ) {
  int width = args->width;
  int height = args->height;

  int **plot = memory_open( sizeof( int * ) * width );
  plot[0] = memory_open( sizeof( int ) * width * height );

  /** Adjust the memory offsets */
  for( int i = 0; i < width; i++ ) {
    plot[ i ] = (*plot + height * i);
  }

  return plot;
}

void mandelbrot_plot_close( int **plot ) {
  memory_close( plot );
}

int mandelbrot_escape( double complex c, int power, int max_iterate ) {
  double complex z = 0;
  int n = 0;
  int zabs = 0;

  /* Terminate if the complex value is iterating towards infinity. */
  while( cabs( z ) <= 2 && n < max_iterate ) {
    z = cpow( z, power ) + c;
    n++;
  }

  /* Renormalize - http://linas.org/art-gallery/escape/escape.html */
  return n >= max_iterate ? max_iterate : (n + 1 - log( log2( cabs( z ) ) ));
}

void *mandelbrot_compute( void *params ) {
  mandelbrot_parameters *parameters = params;
  struct arguments *args = parameters->arguments;
  struct region *region = parameters->region;
  Image image = parameters->image;
  int **plot = parameters->plot;

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

      double complex c = x_real + y_imag * I;

      plot[x][y] = mandelbrot_escape( c, 2, i );
    }
  }

  pthread_exit( NULL );
}

double mandelbrot_nonlinear( int iterations, struct arguments *args ) {
  int max_iterations = args->iterations;
  return (cos( (1.0 * iterations / max_iterations) * M_PI + M_PI) + 1) / 2;
}

void mandelbrot_render( int **plot, Image image, struct arguments *args ) {
  int max_iterations = args->iterations;

  /* Find the minimum and maximum values to normalise over */

  for( int x = 0; x < args->width; x++ ) {
    for( int y = 0; y < args->height; y++ ) {
      int iterations = plot[x][y];

      double i = mandelbrot_nonlinear( iterations, args );

      double h = 360.0 * i;
      double s = 1.0;
      double v = (iterations < max_iterations ? 1.0 : 0.0);

      double r = 0;
      double g = 0;
      double b = 0;

      colour_hsv_to_rgb( h, s, v, &r, &g, &b );

      image_pixel( image, x, y, r * 255, g * 255, b * 255 );
    }
  }
}

