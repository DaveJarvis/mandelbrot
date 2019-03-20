#include "mandelbrot.h"
#include "image.h"
#include "options.h"
#include "threads.h"
#include "errors.h"

/**
 * Draws the Mandelbrot Set as a colourful image.
 */
int main( int c, char **v ) {
  struct arguments arguments;

  options_init( &arguments );
  argp_parse( &argp, c, v, 0, 0, &arguments );

  int threads = thread_cpu_count( arguments.threads );
  pthread_t *thread_ids = thread_open( threads );

  mandelbrot_parameters **p =
    memory_open( sizeof( mandelbrot_parameters * ) * threads );

  Image image = image_open( arguments.width, arguments.height );
  int **plot = mandelbrot_plot_open( &arguments );

  /**
   * Abort if insufficent memory.
   */
  if( plot == NULL || image == NULL || p == NULL || thread_ids == NULL ) {
    mandelbrot_plot_close( plot, &arguments );
    image_close( image );
    memory_close( p );
    thread_close( thread_ids );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  /**
   * Compute the Mandelbrot Set escape iterations.
   */
  for( int i = 0; i < threads; i++ ) {
    mandelbrot_parameters *parameters = mandelbrot_parameters_open();
    struct region *region = image_region_open( image, i, threads );

    parameters->arguments = &arguments;
    parameters->image = image;
    parameters->region = region;
    parameters->plot = plot;

    p[i] = parameters;

    pthread_create( &thread_ids[i], NULL, mandelbrot_compute, parameters );
  }

  /**
   * Wait for the threads to finish their computations.
   */
  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    mandelbrot_parameters *parameters = p[i];
    struct region *region = parameters->region;

    image_region_close( region );
    mandelbrot_parameters_close( parameters );
  }

	int iterations = arguments.iterations;

	/**
   * Colourise the image.
	 */
  for( int x = 0; x < arguments.width; x++ ) {
    for( int y = 0; y < arguments.height; y++ ) {
			int value = plot[x][y];
      int saturation = 255 - (int)(value * (255.0 / iterations));

      image_pixel( image, x, y, saturation );
    }
  }

  /**
   * Free up resources and then save the file.
   */
  mandelbrot_plot_close( plot, &arguments );

  image_save( image, arguments.filename );
  image_close( image );
  memory_close( p );
  thread_close( thread_ids );

  return 0;
}

