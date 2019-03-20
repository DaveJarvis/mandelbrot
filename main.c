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

  /* Determine height in relation to width */
  arguments.height = arguments.width / (1.0 + (1.0 /
    (arguments.plot_r2 - arguments.plot_r1)));

  int threads = thread_cpu_count( arguments.threads );
  pthread_t *thread_ids = thread_open( threads );

  mandelbrot_parameters **p =
    memory_open( sizeof( mandelbrot_parameters * ) * threads );

  Image image = image_open( arguments.width, arguments.height );
  int **plot = mandelbrot_plot_open( &arguments );

  /* Abort if insufficent memory. */
  if( plot == NULL || image == NULL || p == NULL || thread_ids == NULL ) {
    mandelbrot_plot_close( plot, &arguments );
    image_close( image );
    memory_close( p );
    thread_close( thread_ids );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  /* Compute the Mandelbrot Set escape iterations. */
  for( int i = 0; i < threads; i++ ) {
    mandelbrot_parameters *parameters = mandelbrot_parameters_open();
    struct region *region = image_region_open( image, i, threads );

    parameters->arguments = &arguments;
    parameters->image = image;
    parameters->region = region;

    /* Shared across all threads. */
    parameters->plot = plot;

    /* Retain a reference for free'ing memory. */
    p[i] = parameters;

    /* Compute the Mandelbrot Set escape iterations. */
    pthread_create( &thread_ids[i], NULL, mandelbrot_compute, parameters );
  }

  /* Wait for the threads to finish their computations. */
  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    mandelbrot_parameters *parameters = p[i];
    struct region *region = parameters->region;

    image_region_close( region );
    mandelbrot_parameters_close( parameters );
  }

  /* Draw an image using the plotted values. */
  mandelbrot_render( plot, image, &arguments );

  /* Free up resources and then save the file. */
  mandelbrot_plot_close( plot, &arguments );

  image_save( image, arguments.filename );
  image_close( image );
  memory_close( p );
  thread_close( thread_ids );

  return 0;
}

