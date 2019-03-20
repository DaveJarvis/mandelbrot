#ifndef __H_THREADS
#define __H_THREADS

#include <pthread.h>
#include <unistd.h>

#include "options.h"
#include "image.h"
#include "memory.h"

struct thread_parameters {
  struct arguments *arguments;
  struct region *region;
  int **plot;

  Image image;
};

/** 
 * Returns memory for storing a list of thread IDs.
 */
pthread_t *thread_open( int threads );

/**
 * Deallocates memory for thread IDs.
 */
void thread_close( pthread_t *thread_ids );

/**
 * Allocates enough memory to hold parameters for each distinct thread.
 */
struct thread_parameters *thread_parameters_open();

/**
 * Called to release memory allocated from thread_parameters_open.
 */
void thread_parameters_close( struct thread_parameters *parameters );

/**
 * Returns the number of processors available, or the default value if
 * set.
 */
long thread_cpu_count( long default_value );

#endif

