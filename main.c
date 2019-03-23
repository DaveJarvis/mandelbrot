#include "mandelbrot.h"
#include "options.h"

/**
 * Draws the Mandelbrot Set as an image.
 */
int main( int c, char **v ) {
  struct arguments arguments;
  mandelbrot_parameters fractal = arguments.fractal;

  mandelbrot_parameters_init( &fractal );
  options_init( &arguments );

  argp_parse( &argp, c, v, 0, 0, &arguments );
  log_info( "Start: %s", doc_program );

  log_info( "Determine number of CPUs available" );
  int threads = (int)thread_cpu_count( arguments.threads );
  pthread_t *thread_ids = thread_open( threads );

  log_info( "Use %d threads", threads );
  log_info( "Use image dimensions %d x %d pixels",
    fractal.width, fractal.height );

  log_info( "Allocate memory for fractal parameters" );
  mandelbrot_parameters **p =
    memory_open( (size_t)sizeof( mandelbrot_parameters * ) * (size_t)threads );

  log_info( "Allocate memory for canvas" );
  fractal.image = image_open( fractal.width, fractal.height );
  mandelbrot_plot_open( &fractal );

  log_info( "Check for sufficient memory" );
  if( fractal.plot == NULL ||
      fractal.image == NULL ||
      p == NULL ||
      thread_ids == NULL ) {
    mandelbrot_plot_close( &fractal );
    image_close( fractal.image );
    memory_close( p );
    thread_close( thread_ids );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  log_info( "Start threads to calculate escape iterations" );
  for( int i = 0; i < threads; i++ ) {
    mandelbrot_parameters *worker = mandelbrot_parameters_open();
    mandelbrot_parameters_copy( &fractal, worker );

    struct region *region = image_region_open( fractal.image, i, threads );

    worker->region = region;

    // Retain a reference for free'ing memory.
    p[i] = worker;

    log_info( "Thread %03d region: (%04d, %04d)-(%04d, %04d)",
      i, region->x1, region->y1, region->x2, region->y2 );

    // Compute the iterations within a thread for a particular region.
    pthread_create( &thread_ids[i], NULL, mandelbrot_compute, worker );
  }

  log_info( "Wait for threads to finish" );
  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    mandelbrot_parameters *worker = p[i];
    struct region *region = worker->region;

    image_region_close( region );
    mandelbrot_parameters_close( worker );
  }

  log_info( "Release thread memory" );
  memory_close( p );
  thread_close( thread_ids );

  log_info( "Render image using calculated iterations" );
  mandelbrot_paint( &fractal );

  log_info( "Release memory used by calculated iterations" );
  mandelbrot_plot_close( &fractal );

  log_info( "Save image to file" );
  image_save( fractal.image, arguments.filename );

  log_info( "Release memory for image" );
  image_close( fractal.image );

  log_info( "Stop" );
  return 0;
}

