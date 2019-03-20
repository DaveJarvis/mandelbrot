#include "errors.h"

void error_terminate( int error_level, char *message ) {
  fprintf( stderr, "%s\n", message );
  exit( error_level );
}

