#ifndef H_FRACTAL_MEMORY
#define H_FRACTAL_MEMORY

#include <stdlib.h>
#include <stdio.h>

/**
 * Allocates the given amount of memory.
 *
 * @param size The number of bytes to allocate.
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

