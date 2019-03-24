#include "logging.h"

struct logging_log {
  int level;
};

static pthread_mutex_t lock;

static struct logging_log LOG = { LOG_FATAL };

static const char *LOG_LEVELS[] = {
  "TRACE", "DEBUG", "POSTS", "ALERT", "ERROR", "FATAL"
};

void logging_set_level( int level ) {
  LOG.level = level;
}

__attribute__((__format__ (__printf__, 4, 0)))
void logging_log( int level, const char *src, int line, char *message, ... ) {
  if( level >= LOG.level ) {
    pthread_mutex_lock( &lock );

    struct timespec clock;    
    clock_gettime( CLOCK_REALTIME, &clock );

    struct tm *time = localtime( &clock.tv_sec );

    // Convert nanoseconds to milliseconds.
    long millis = (long)(clock.tv_nsec / 1000000L);

    printf( "[%s %02d:%02d:%02d.%.3ld] ",
      LOG_LEVELS[ level ], time->tm_hour, time->tm_min, time->tm_sec, millis );

    if( LOG.level < LOG_INFO ) {
      printf( "(%s:%d) ", src, line );
    }

    va_list argptr;
    va_start( argptr, message );
    vfprintf( stdout, message, argptr );
    va_end( argptr );

    printf( "\n" );

    pthread_mutex_unlock( &lock );
  }
}

