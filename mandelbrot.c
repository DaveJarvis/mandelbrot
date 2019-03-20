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

int **mandelbrot_plot_open( struct arguments *arguments ) {
  int width = arguments->width;
  int height = arguments->height;

  int **plot = memory_open( sizeof( int * ) * width );
  plot[0] = memory_open( sizeof( int ) * width * height );

  /** Adjust the memory offsets */
  for( int i = 0; i < width; i++ ) {
    plot[ i ] = (*plot + height * i);
  }

  return plot;
}

void mandelbrot_plot_close( int **plot, struct arguments *arguments ) {
  int width = arguments->width;

  memory_close( plot );
}

int mandelbrot_escape( double complex c, int power, int max_iterate ) {
  double complex z = 0;
  int n = 0;
  int zabs = 0;

  /**
   * Terminate if the complex value is iterating towards infinity.
   */
  while( cabs( z ) <= 2 && n < max_iterate ) {
    z = cpow( z, power ) + c;
    n++;
  }

  z = z * z + c;
  z = z * z + c;
  n += 2;

  /**
   * Renormalize the Mandelbrot Escape
   *
   * http://linas.org/art-gallery/escape/escape.html
   */
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

void mandelbrot_render( int **plot, Image image, struct arguments *arguments ) {
  int iterations = arguments->iterations;

  for( int x = 0; x < arguments->width; x++ ) {
    for( int y = 0; y < arguments->height; y++ ) {
      int value = plot[x][y];
      int s = 255 - (int)(value * (255.0 / iterations));

      image_pixel( image, x, y, s, s, s );
    }
  }
}

