#ifndef H_MANDELBROT_THREADS
#define H_MANDELBROT_THREADS

#include <pthread.h>
#include <unistd.h>

#include "image.h"
#include "memory.h"

#define DEFAULT_UNDEFINED 0L
#define DEFAULT_THREADS DEFAULT_UNDEFINED

/** 
 * Returns memory for storing a list of thread IDs.
 */
pthread_t *thread_open( int threads );

/**
 * Deallocates memory for thread IDs.
 */
void thread_close( pthread_t *thread_ids );

/**
 * Returns the number of processors available, or the default value if
 * set.
 */
long thread_cpu_count( long default_value );

#endif

