#ifndef H_FRACTAL_LOGGING
#define H_FRACTAL_LOGGING

#include <inttypes.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/**
 * List of log levels.
 */
enum { LOG_TRACE, LOG_DEBUG, LOG_POSTS, LOG_ALERT, LOG_ERROR, LOG_FATAL };

#define log_trace(...) logging_log( LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__ )
#define log_debug(...) logging_log( LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__ )
#define log_info(...)  logging_log( LOG_POSTS, __FILE__, __LINE__, __VA_ARGS__ )
#define log_warn(...)  logging_log( LOG_ALERT, __FILE__, __LINE__, __VA_ARGS__ )
#define log_error(...) logging_log( LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__ )
#define log_fatal(...) logging_log( LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__ )

/**
 * Changes the logging level to give different levels of information while
 * the program is running.
 *
 * @param level The new logging level.
 */
void logging_set_level( int level );

/**
 * Conditionally writes a message to standard output. The message will be
 * formatted using printf, so any number of arguments afterwards are possible.
 * Logs the source file, line number, and message if the level is above
 * the actively set logging level.
 *
 * @param level One of the enumerated logging levels.
 * @param src Name of the source file containing the logged message.
 * @param line Line number in the source file.
 * @param message Text to write to standard output.
 *
 * @see http://clang.llvm.org/docs/AttributeReference.html#format
 */
void logging_log( int level, const char *src, int line, char *message, ... );

#endif

