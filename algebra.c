#include "algebra.h"

double cdot( double complex z1, double complex z2 ) {
  double complex zbar = conj( z1 );
  double complex z = zbar * z2;
  return creal( z );
}

