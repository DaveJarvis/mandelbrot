#ifndef H_FRACTAL_THREADS
#define H_FRACTAL_THREADS

#include <pthread.h>
#include <unistd.h>

#include "args.h"
#include "memory.h"

/** 
 * Returns memory for storing a list of thread IDs.
 *
 * @param threads The number of threads to use.
 *
 * @return A pointer to the thread identifier structure.
 */
pthread_t *thread_open( int threads );

/**
 * Deallocates memory for thread IDs.
 *
 * @param thread_ids Reference to the value returned by thread_open(int).
 */
void thread_close( pthread_t *thread_ids );

/**
 * Returns the number of processors available, or the default value if
 * set. On an octocore processor, 128 threads seems to be optimal.
 *
 * @param default_value Number of threads to use; set to DEFAULT_UNDEFINED to
 * use the active number of CPUs.
 *
 * @return The number of threads or CPUs to use.
 */
long thread_cpu_count( long default_value );

#endif

