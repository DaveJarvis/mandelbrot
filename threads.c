#include "threads.h"

struct thread_parameters *thread_parameters_open() {
  struct thread_parameters *parameters =
    malloc( sizeof( struct thread_parameters ) );

  if( parameters != NULL ) {
    parameters->arguments = NULL;
    parameters->region = NULL;
    parameters->image = NULL;
  }

  return parameters;
}

void thread_parameters_close( struct thread_parameters *parameters ) {
  if( parameters != NULL ) {
    free( parameters );
  }
}

long thread_cpu_count() {
  return sysconf( _SC_NPROCESSORS_ONLN );
}

