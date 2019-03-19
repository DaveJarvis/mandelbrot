#ifndef __H_THREADS
#define __H_THREADS

#include <pthread.h>
#include <unistd.h>

#include "options.h"
#include "image.h"

struct thread_parameters {
  struct arguments *arguments;
  struct region *region;
  Image image;
};

/**
 * Allocates enough memory to hold parameters for each distinct thread.
 */
struct thread_parameters *thread_parameters_open();

/**
 * Called to release memory allocated from thread_parameters_open.
 */
void thread_parameters_close( struct thread_parameters *parameters );

/**
 * Returns the number of processors available.
 */
long thread_cpu_count();

#endif

