#include "mandelbrot.h"

/**
 * Draws the Mandelbrot Set as a colourful image.
 */
int main( int c, char **v ) {
  struct arguments arguments;

  options_init( &arguments );
  argp_parse( &argp, c, v, 0, 0, &arguments );

  log_verbose( &arguments, "Determine number of CPUs available" );
  int threads = thread_cpu_count( arguments.threads );
  pthread_t *thread_ids = thread_open( threads );

  mandelbrot_parameters **p =
    memory_open( sizeof( mandelbrot_parameters * ) * threads );

  log_verbose( &arguments, "Allocate memory for canvas" );
  Image image = image_open( arguments.width, arguments.height );
  int **plot = mandelbrot_plot_open( &arguments );

  log_verbose( &arguments, "Check for sufficient memory" );
  if( plot == NULL || image == NULL || p == NULL || thread_ids == NULL ) {
    mandelbrot_plot_close( plot, &arguments );
    image_close( image );
    memory_close( p );
    thread_close( thread_ids );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  log_verbose( &arguments, "Start threads to calculate escape iterations" );
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

    /* Compute the iterations within a thread for a particular region. */
    pthread_create( &thread_ids[i], NULL, mandelbrot_compute, parameters );
  }

  log_verbose( &arguments, "Wait for threads to finish calculations" );
  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    mandelbrot_parameters *parameters = p[i];
    struct region *region = parameters->region;

    image_region_close( region );
    mandelbrot_parameters_close( parameters );
  }

  log_verbose( &arguments, "Release memory for threads" );
  memory_close( p );
  thread_close( thread_ids );

  log_verbose( &arguments, "Draw image using calculated iterations" );
  mandelbrot_render( plot, image, &arguments );

  log_verbose( &arguments, "Release memory used by calculated iterations" );
  mandelbrot_plot_close( plot, &arguments );

  log_verbose( &arguments, "Save image to file" );
  image_save( image, arguments.filename );

  log_verbose( &arguments, "Release memory for image" );
  image_close( image );

  return 0;
}

