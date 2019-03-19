#include "mandelbrot.h"
#include "image.h"
#include "options.h"
#include "threads.h"

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

void *generate_image( void *params ) {
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

      int iter = mandelbrot( c, i );
      int saturation = 255 - (int)(iter * (255.0 / i));

      image_pixel( image, x, y, saturation );
    }
  }

  pthread_exit( NULL );
}

/**
 * Draw mandelbrot to an image.
 */
int main( int c, char **v ) {
  struct arguments arguments;

  options_init( &arguments );
  argp_parse( &argp, c, v, 0, 0, &arguments );

  int threads = arguments.threads;
  pthread_t *thread_ids = malloc( sizeof( pthread_t ) * threads );

  if( thread_ids != NULL ) {
    Image image = image_open( arguments.width, arguments.height );

    struct thread_parameters **p =
      malloc( sizeof( struct thread_parameters * ) * threads );

    for( int i = 0; i < threads; i++ ) {
      struct thread_parameters *parameters = thread_parameters_open();
      struct region *region = image_region_open( image, i, threads );

      parameters->arguments = &arguments;
      parameters->image = image;
      parameters->region = region;

      p[i] = parameters;

      pthread_create( &thread_ids[i], NULL, generate_image, parameters );
    }

    for( int i = 0; i < threads; i++ ) {
      pthread_join( thread_ids[i], NULL );

      struct thread_parameters *parameters = p[i];
      struct region *region = parameters->region;

      image_region_close( region );
      thread_parameters_close( parameters );
    }

    image_save( image, arguments.filename );
    image_close( image );
    free( thread_ids );
  }

  return 0;
}

