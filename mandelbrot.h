#ifndef __H_MANDELBROT
#define __H_MANDELBROT

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "memory.h"
#include "options.h"
#include "threads.h"

int **mandelbrot_plot_open( struct arguments *arguments );

void mandelbrot_plot_close( int **plot, struct arguments *arguments );

int mandelbrot_escape( double complex c, int power, int max_iterate );

void *mandelbrot_image( void *params );

#endif

