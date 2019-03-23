#ifndef H_FRACTAL_ALGEBRA
#define H_FRACTAL_ALGEBRA

#include <complex.h>
#include <math.h>

/**
 * Returns the dot product of z1 and z2.
 *
 * @param z1 The first term of the dot product.
 * @param z2 The second term of the dot product.
 * @return z1 dot z2
 *
 * @see https://proofwiki.org/wiki/Definition:Dot_Product/Complex
 */
double cdot( double complex z1, double complex z2 );

#endif

