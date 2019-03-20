#include "errors.h"

void error_terminate( int exit_code, char *message ) {
  fprintf( stderr, "%s\n", message );
  exit( exit_code );
}

