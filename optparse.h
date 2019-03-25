#ifndef H_FRACTAL_OPTPARSE
#define H_FRACTAL_OPTPARSE

/**
 * Optparse is a public domain, portable, reentrant, embeddable,
 * getopt-like option parser. It's a single header file and can be
 * trivially dropped into any project. It supports POSIX getopt option
 * strings, GNU-style long options, argument permutation, and
 * subcommand processing.
 *
 * @see https://github.com/skeeto/optparse
 * @author Christopher Wellons
 */

/** Unknown command-line argument provided. */
#define OPTPARSE_MSG_INVALID "invalid option"
/** Missing command-line argument option . */
#define OPTPARSE_MSG_MISSING "option requires an argument"
/** Command-line argument given option, none expected. */
#define OPTPARSE_MSG_TOOMANY "option takes no arguments"

struct optparse {
  char **argv;
  int permute;
  int optind;
  int optopt;
  char *optarg;
  char errmsg[64];
  int subopt;
};

enum optparse_argtype {
  OPTPARSE_NONE,
  OPTPARSE_REQUIRED,
  OPTPARSE_OPTIONAL
};

struct optparse_long {
  const char *longname;
  int shortname;
  enum optparse_argtype argtype;
  const char *description;
};

/**
 * Initializes the parser state.
 */
void optparse_init(struct optparse *options, char **argv);

/**
 * Read the next option in the argv array.
 * @param options state structure for thread-safe execution.
 * @param optstring a getopt()-formatted option string.
 * @return the next option character, -1 for done, or '?' for error
 *
 * Just like getopt(), a character followed by no colons means no
 * argument. One colon means the option has a required argument. Two
 * colons means the option takes an optional argument.
 */
int optparse(struct optparse *options, const char *optstring);

/**
 * Handles GNU-style long options in addition to getopt() options.
 * This works a lot like GNU's getopt_long(). The last option in
 * longopts must be all zeros, marking the end of the array. The
 * longindex argument may be NULL.
 */
int optparse_long(struct optparse *options,
          const struct optparse_long *longopts,
          int *longindex);

/**
 * Determines whether the given index into the long options is valid.
 *
 * @return !0 The indexed reference has no set values.
 */
int optparse_longopts_end(const struct optparse_long *longopts, int i);

/**
 * Used for stepping over non-option arguments.
 * @return the next non-option argument, or NULL for no more arguments
 *
 * Argument parsing can continue with optparse() after using this
 * function. That would be used to parse the options for the
 * subcommand returned by optparse_arg(). This function allows you to
 * ignore the value of optind.
 */
char *optparse_arg(struct optparse *options);

#endif
