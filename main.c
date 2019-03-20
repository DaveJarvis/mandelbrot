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

  struct thread_parameters **p =
    memory_open( sizeof( struct thread_parameters * ) * threads );

  Image image = image_open( arguments.width, arguments.height );
  int **plot = mandelbrot_plot_open( &arguments );

  if( plot == NULL || image == NULL || p == NULL || thread_ids == NULL ) {
    mandelbrot_plot_close( plot, &arguments );
    image_close( image );
    memory_close( p );
    thread_close( thread_ids );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  for( int i = 0; i < threads; i++ ) {
    struct thread_parameters *parameters = thread_parameters_open();
    struct region *region = image_region_open( image, i, threads );

    parameters->arguments = &arguments;
    parameters->image = image;
    parameters->region = region;
    parameters->plot = plot;

    p[i] = parameters;

    pthread_create( &thread_ids[i], NULL, mandelbrot_image, parameters );
  }

  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    struct thread_parameters *parameters = p[i];
    struct region *region = parameters->region;

    image_region_close( region );
    thread_parameters_close( parameters );
  }

  mandelbrot_plot_close( plot, &arguments );

  image_save( image, arguments.filename );
  image_close( image );
  memory_close( thread_ids );

  return 0;
}

