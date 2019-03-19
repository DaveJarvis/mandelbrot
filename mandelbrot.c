#include "mandelbrot.h"
#include "image.h"

double complex f( double complex z, double complex c, int iter ) {
  double complex zn = cpow( z, 2 ) + c;

  return iter - 1 > 0 ? f( zn, c, --iter ) : zn;
}

/**
 * Draw mandelbrot to an image.
 */
int main( int c, char **v ) {
  Image image = image_open( IMAGE_WIDTH, IMAGE_HEIGHT );

  int black = image_colour( image, 0x00, 0x00, 0x00 );
  int white = image_colour( image, 0xFF, 0xFF, 0xFF );

  double x = -2;

  while( x < 2 ) {
    double y = -2;

    while( y < 2 ) {
      double complex result = f( 0 * I, x + y * I, 2 );

      double rx = creal( result );
      double ry = cimag( result );

      if( rx > 2 ) {
        printf( "plot (%+.4f %+.4f)\n", x, y );
        image_pixel( image, x * IMAGE_WIDTH / 4, y * IMAGE_HEIGHT / 4, white );
      }

      y += ITERATION_Y;
    }

    x += ITERATION_X;
  }

  image_save( image, "image.png" );

  image_close( image );
}

