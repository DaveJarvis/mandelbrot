#include "args.h"
#include "fractal.h"
#include "settings.h"

/**
 * Draws a fractal.
 */
int main( int c, char **v ) {
  global_args args;
  args_parse( v, &args );

  settings_interpret( v, &args );

  log_info( "Determine number of threads" );
  int threads = (int)thread_cpu_count( args.threads );

  fractal_parameters fractal;
  fractal_parameters_init( &fractal, &args );

  log_info( "Allocate memory for canvas" );
  fractal.image = image_open( fractal.width, fractal.height );

  log_info( "Allocate memory for fractal parameters" );
  fractal_parameters **p =
    memory_open( (size_t)sizeof( fractal_parameters * ) * (size_t)threads );

  log_info( "Allocate memory for thread identifiers" );
  pthread_t *thread_ids = thread_open( threads );

  log_info( "Allocate memory for fractal palette" );
  fractal.colour_base = colour_open();

  log_info( "Verify memory allocations" );
  if( fractal.colour_base == NULL ||
      thread_ids == NULL ||
      p == NULL ||
      fractal.image == NULL ) {
    colour_close( fractal.colour_base );
    thread_close( thread_ids );
    memory_close( p );
    image_close( fractal.image );
    error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
  }

  log_info( "Parse base palette colour" );
  colour_parse( args.palette, fractal.colour_base );

  log_info( "Validate fractal settings" );
  fractal_parameters_validate( &fractal );

  log_info( "Setup: Canvas %d x %d pixels", fractal.width, fractal.height );
  log_info( "Setup: (%f, %f) centre", fractal.cx, fractal.cy );
  log_info( "Setup: %f zoom", fractal.zoom );
  log_info( "Setup: %d threads", threads );
  log_info( "Setup: hsv(%f, %f, %f)",
    fractal.colour_base->hsv[0],
    fractal.colour_base->hsv[1],
    fractal.colour_base->hsv[2]
  );

  log_info( "Start threads to calculate escape iterations" );
  for( int i = 0; i < threads; i++ ) {
    fractal_parameters *worker = fractal_parameters_open();

    if( worker == NULL ) {
      // Insufficient memory; let the OS clean up the dangling pointers.
      error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
    }

    fractal_parameters_copy( &fractal, worker );

    struct region *region = image_region_open( fractal.image, i, threads );

    if( region == NULL ) {
      error_terminate( ERROR_MEMORY, ERROR_MEMORY_TEXT );
    }

    worker->region = region;

    // Retain a reference for free'ing memory.
    p[i] = worker;

    log_info( "Thread %03d region: (%04d, %04d)-(%04d, %04d)",
      i, region->x1, region->y1, region->x2, region->y2 );

    // Compute the iterations within a thread for a particular region.
    if( pthread_create( &thread_ids[i], NULL, fractal_compute, worker ) ) {
      // If pthread_create returns non-zero, then the call failed.
      error_terminate( ERROR_THREAD, ERROR_THREAD_TEXT );
    }
  }

  log_info( "Wait for threads to finish" );
  for( int i = 0; i < threads; i++ ) {
    pthread_join( thread_ids[i], NULL );

    fractal_parameters *worker = p[i];
    struct region *region = worker->region;

    image_region_close( region );
    fractal_parameters_close( worker );
  }

  log_info( "Save fractal as: %s", args.filename );
  image_save( fractal.image, args.filename );

  // Release memory in reverse order of allocation.
  log_info( "Release memory for fractal palette" );
  colour_close( fractal.colour_base );

  log_info( "Release memory for thread identifiers" );
  thread_close( thread_ids );

  log_info( "Release memory for fractal parameters" );
  memory_close( p );

  log_info( "Release memory for canvas" );
  image_close( fractal.image );

  log_info( "Done" );
  return 0;
}

