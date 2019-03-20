#include "threads.h"

pthread_t *thread_open( int threads ) {
  return memory_open( sizeof( pthread_t ) * threads );
}

void thread_close( pthread_t *thread_ids ) {
  memory_close( thread_ids );
}

struct thread_parameters *thread_parameters_open() {
  struct thread_parameters *parameters =
    memory_open( sizeof( struct thread_parameters ) );

  if( parameters != NULL ) {
    parameters->arguments = NULL;
    parameters->region = NULL;
    parameters->image = NULL;
    parameters->plot = NULL;
  }

  return parameters;
}

void thread_parameters_close( struct thread_parameters *parameters ) {
  if( parameters != NULL ) {
    memory_close( parameters );
  }
}

long thread_cpu_count( long default_value ) {
  return default_value == DEFAULT_UNDEFINED ?
    sysconf( _SC_NPROCESSORS_ONLN ) :
    default_value;
}

