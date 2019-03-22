#ifndef H_MANDELBROT_IMAGE
#define H_MANDELBROT_IMAGE

#include <math.h>
#include <gd.h>

#include "colours.h"
#include "options.h"
#include "memory.h"

struct region {
  int x1;
  int y1;
  int x2;
  int y2;
};

typedef gdImagePtr Image;

/**
 * Opens an image of the given dimensions.
 *
 * @param width The number of pixels from left to right.
 * @param height The number of pixels from top to bottom.
 */
Image image_open( int width, int height );

/**
 * Opens an image region boundary. The pointer to a region returned by
 * this function must be closed using image_region_close. The regions
 * created by this function should be non-overlapping so that individual
 * threads can draw independently.
 *
 * @param image The image that was opened for drawing.
 * @param n The region index (0 through regions - 1).
 * @param regions The number of regions to create.
 */
struct region *image_region_open( Image image, int n, int regions );

/**
 * Releases memory set aside for an image region boundary.
 *
 * @param region The region to deallocate.
 */
void image_region_close( struct region *region );

/**
 * Create a new grayscale palette colour index for the given image.
 *
 * @param image Pointer to the image structure.
 * @param s Grayscale colour value.
 */
int image_colour_grayscale( Image image, int s );

/**
 * Draw a pixel on the image at the given coordinates with the given
 * RGB colour. This converts the 8-bit RGB triplet to a 24-bit colour.
 *
 * @param r Red channel component (0 - 255)
 * @param g Green channel component (0 - 255)
 * @param b Blue channel component (0 - 255)
 */
void image_pixel( Image image, int x, int y, int r, int g, int b );

/**
 * Export the given image to the specified file.
 */
void image_save( Image image, char *filename );

/**
 * Release the image memory.
 */
void image_close( Image image );

#endif

