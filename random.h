#ifndef H_FRACTAL_RANDOM
#define H_FRACTAL_RANDOM

#include <stdint.h>
#include <string.h>

#define RANDOM_STATE_SIZE 5

/**
 * Populates the random number generator seeds.
 *
 * @param state Seeded with non-zero values.
 */
void random_init( uint32_t state[ static RANDOM_STATE_SIZE ] );

/**
 * Algorithm "Mulberry32".
 *
 * @param x The value to use to generate a random seed.
 *
 * @return A randomized value for use with random_init.
 *
 * @author Tommy Ettinger
 */
uint32_t random_seed( uint32_t x );

/**
 * Algorithm "xorwow".
 *
 * @param state Seed with non-zero values (call random_init).
 *
 * @return A pseudo-random number.
 *
 * @author George Marsaglia
 */
uint32_t random_next( uint32_t state[ static RANDOM_STATE_SIZE ] );

#endif

