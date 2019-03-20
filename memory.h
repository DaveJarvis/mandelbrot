#ifndef __H_MEMORY
#define __H_MEMORY

#include <stdlib.h>

void *memory_open( size_t size );

void memory_close( void *ptr );

#endif

