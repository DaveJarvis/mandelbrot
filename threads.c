#include "threads.h"

pthread_t *thread_open( int threads ) {
  return memory_open( (size_t)sizeof( pthread_t ) * (size_t)threads );
}

void thread_close( pthread_t *thread_ids ) {
  memory_close( thread_ids );
}

long thread_cpu_count( long default_value ) {
  // If no thread count has been set, use all available CPUs.
  return default_value == ARG_UNDEFINED ?
    sysconf( _SC_NPROCESSORS_ONLN ) :
    default_value;
}

