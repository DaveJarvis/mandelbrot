#include "logging.h"

void log_verbose( struct arguments *arguments, char *message, ... ) {
  if( arguments->verbose ) {
    struct timespec clock;    
    clock_gettime( CLOCK_REALTIME, &clock );

    struct tm *time = localtime( &clock.tv_sec );

    /* Convert nanoseconds to milliseconds. */
    long millis = (long)(clock.tv_nsec / 1000000L);

    va_list argptr;
    va_start( argptr, message );

    printf( "[%02d:%02d:%02d.%.3ld] ",
      time->tm_hour, time->tm_min, time->tm_sec, millis );

    vfprintf( stdout, message, argptr );

    printf( "\n" );

    va_end( argptr );
  }
}

