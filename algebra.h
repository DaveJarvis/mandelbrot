#ifndef __H_ALGEBRA
#define __H_ALGEBRA

#include <complex.h>
#include <math.h>

/* https://stackoverflow.com/a/3437484/59087 */
#define max(a,b) \
 ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })

#define min(a,b) \
 ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })

/**
 * Returns the dot product of z1 and z2.
 *
 * @see https://proofwiki.org/wiki/Definition:Dot_Product/Complex
 */
double cdot( double complex z1, double complex z2 );

#endif

