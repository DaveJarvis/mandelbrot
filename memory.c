#include "memory.h"

void *memory_open( size_t size ) {
  return malloc( size );
}

void memory_close( void *ptr ) {
  if( ptr != NULL ) {
    free( ptr );
  }
}

