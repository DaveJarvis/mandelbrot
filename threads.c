#include "threads.h"

pthread_t *thread_open( int threads ) {
  return memory_open( sizeof( pthread_t ) * threads );
}

void thread_close( pthread_t *thread_ids ) {
  memory_close( thread_ids );
}

long thread_cpu_count( long default_value ) {
  return default_value == DEFAULT_UNDEFINED ?
    sysconf( _SC_NPROCESSORS_ONLN ) :
    default_value;
}

