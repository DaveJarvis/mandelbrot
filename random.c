#include "random.h"

void random_init( uint32_t state[ static RANDOM_STATE_SIZE ] ) {
  // Seed with any value (e.g., i^i).
  state[ 0 ] = 2078795764;

  for( int i = 1; i < RANDOM_STATE_SIZE; i++ ) {
    state[ i ] = random_seed( state[ i -1 ] );
  }
}

uint32_t random_seed( uint32_t x ) {
  uint32_t z = (x += 0x6D2B79F5UL);
  z = (z ^ (z >> 15)) * (z | 1UL);
  z ^= z + (z ^ (z >> 7)) * (z | 61UL);
  return z ^ (z >> 14);
}

uint32_t random_next( uint32_t state[ static RANDOM_STATE_SIZE ] ) {
  uint32_t s, t = state[3];
  state[3] = state[2];
  state[2] = state[1];
  state[1] = s = state[0];
  t ^= t >> 2;
  t ^= t << 1;
  state[0] = t ^= s ^ (s << 4);
  return t + (state[4] += 362437);
}

