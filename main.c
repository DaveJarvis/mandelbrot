#include "fractal.h"
#include "options.h"

/**
 * Draws the Mandelbrot Set as an image.
 */
int main( int c, char **v ) {
  fractal_parameters fractal;
  fractal_parameters_init( &fractal );

  struct arguments arguments;
  arguments.fractal = &fractal;
  options_init( &arguments );
  argp_parse( &argp, c, v, 0, 0, &arguments );

  log_info( "%s", doc_program );

  log_info( "Validate fractal settings" );
  fractal_parameters_validate( &fractal );

  log_info( "Determine number of threads" );
  int threads = (int)thread_cpu_count( arguments.threads );

  log_info( "Allocate memory for thread identifiers" );
  pthread_t *thread_ids = thread_open( threads );

  log_info( "Allocate memory for fractal parameters" );
  fractal_parameters **p =
    memory_open( (size_t)sizeof( fractal_parameters * ) * (size_t)threads );

  log_info( "Allocate memory for canvas" );
  fractal.image = image_open( fractal.width, fractal.height );

  log_info( "Check that memory allocations succeeded" );
  if( fractal.image == NULL || p == NULL || thread_ids == NULL ) {
    image_close( fractal.image );
    memory_close( p );
    thread_close( thread_ids );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  log_info( "Setup: Canvas %d x %d pixels", fractal.width, fractal.height );
  log_info( "Setup: (%f, %f) centre", fractal.cx, fractal.cy );
  log_info( "Setup: %f zoom", fractal.zoom );
  log_info( "Setup: %d threads", threads );

  log_info( "Start threads to calculate escape iterations" );
  for( int i = 0; i < threads; i++ ) {
    fractal_parameters *worker = fractal_parameters_open();
    fractal_parameters_copy( &fractal, worker );

    struct region *region = image_region_open( fractal.image, i, threads );

    worker->region = region;

    // Retain a reference for free'ing memory.
    p[i] = worker;

    log_info( "Thread %03d region: (%04d, %04d)-(%04d, %04d)",
      i, region->x1, region->y1, region->x2, region->y2 );

    // Compute the iterations within a thread for a particular region.
    pthread_create( &thread_ids[i], NULL, fractal_compute, worker );
  }

  log_info( "Wait for threads to finish" );
  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    fractal_parameters *worker = p[i];
    struct region *region = worker->region;

    image_region_close( region );
    fractal_parameters_close( worker );
  }

  log_info( "Release memory for fractal parameters" );
  memory_close( p );

  log_info( "Release memory for thread identifiers" );
  thread_close( thread_ids );

  log_info( "Save fractal as: %s", arguments.filename );
  image_save( fractal.image, arguments.filename );

  log_info( "Release memory for canvas" );
  image_close( fractal.image );

  log_info( "Done" );
  return 0;
}

