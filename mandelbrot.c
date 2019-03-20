#include "mandelbrot.h"

int **mandelbrot_plot_open( struct arguments *arguments ) {
  int width = arguments->width;
  int height = arguments->height;

  int **result = (int **)memory_open( sizeof( int * ) * width );

  for( int i = 0; i < width; i++ ) {
    result[ i ] = (int *)memory_open( sizeof( int ) * height );
  }

  return result;
}

void mandelbrot_plot_close( int **plot, struct arguments *arguments ) {
  int width = arguments->width;

  for( int i = 0; i < width; i++ ) {
    memory_close( plot[ i ] );
  }

  memory_close( plot );
}

/**
 * Returns the number of iterations before iterating escapes the Mandelbrot
 * Set.
 */
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

/**
 * Run by a single thread to fill in part of a Mandelbrot Set image.
 */
void *mandelbrot_image( void *params ) {
  struct thread_parameters *parameters = params;
  struct arguments *args = parameters->arguments;
  struct region *region = parameters->region;
  Image image = parameters->image;

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

      int iter = mandelbrot_escape( c, 2, i );

      int saturation = 255 - (int)(iter * (255.0 / i));

      image_pixel( image, x, y, saturation );
    }
  }

  pthread_exit( NULL );
}

