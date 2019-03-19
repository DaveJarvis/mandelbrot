#include "mandelbrot.h"
#include "image.h"
#include "options.h"

int mandelbrot( double complex c, int max_iterate ) {
  double complex z = 0;
  int n = 0;
  int zabs = 0;

  while( (zabs = cabs( z )) <= 2 && n < max_iterate ) {
    z = z * z + c;
    n++;
  }

  return n == max_iterate ? max_iterate : (n + 1 - log( log2( zabs ) ));
}

void generate_image( struct arguments arguments ) {
  int w = arguments.width;
  int h = arguments.height;
  int i = arguments.iterations;
  double x1 = arguments.plot_r1;
  double x2 = arguments.plot_r2;
  double y1 = arguments.plot_i1;
  double y2 = arguments.plot_i2;

  Image image = image_open( w, h );

  for( int x = 0; x < w; x++ ) {
    for( int y = 0; y < h; y++ ) {
      double x_real = x1 + (x * 1.0 / w) * (x2 - x1);
      double y_imag = y1 + (y * 1.0 / h) * (y2 - y1);

      double complex c = x_real + y_imag * I;

      int iter = mandelbrot( c, i );
      int saturation = 255 - (int)(iter * (255.0 / i));

      image_pixel( image, x, y, saturation );
    }
  }

  image_save( image, arguments.filename );

  image_close( image );
}

/**
 * Draw mandelbrot to an image.
 */
int main( int c, char **v ) {
  struct arguments arguments;

  options_init( &arguments );

  argp_parse( &argp, c, v, 0, 0, &arguments );

  generate_image( arguments );
}

