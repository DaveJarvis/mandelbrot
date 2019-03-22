#ifndef H_MANDELBROT_MEMORY
#define H_MANDELBROT_MEMORY

#include <stdlib.h>

/**
 * Allocates the given amount of memory.
 *
 * @return NULL The memory could not be allocated.
 */
void *memory_open( size_t size );

/**
 * Releases memory previously allocated with memory_open.
 *
 * @param ptr Pointer to memory block to be closed, can be NULL.
 */
void memory_close( void *ptr );

#endif

