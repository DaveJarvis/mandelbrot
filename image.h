#ifndef H_FRACTAL_IMAGE
#define H_FRACTAL_IMAGE

#include <math.h>
#include <gd.h>

#include "colours.h"

/**
 * Region to be painted by a thread.
 */
struct region {
  /** Upper-left x coordinate. */
  int x1;
  /** Upper-left y coordinate. */
  int y1;
  /** Lower-right x coordinate. */
  int x2;
  /** Lower-right y coordinate. */
  int y2;
};

/**
 * Hides the library data type.
 */
typedef gdImagePtr Image;

/**
 * Opens an image of the given dimensions.
 *
 * @param width The number of pixels from left to right.
 * @param height The number of pixels from top to bottom.
 *
 * @return Pointer to the canvas.
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
 *
 * @return Pointer to the region boundary.
 */
struct region *image_region_open( Image image, int n, int regions );

/**
 * Releases memory set aside for an image region boundary.
 *
 * @param region The region to deallocate.
 */
void image_region_close( struct region *region );

/**
 * Draw a pixel on the image at the given coordinates with the given
 * RGB colour. This converts the 8-bit RGB triplet to a 24-bit colour.
 *
 * @param image Canvas for setting pixels
 * @param x X coordinate to set a pixel
 * @param y Y coordinate to set a pixel
 * @param pixel Red, green, and blue channel components (0 - 255)
 */
void image_pixel( Image image, int x, int y, colour pixel );

/**
 * Export the given image to the specified file.
 *
 * @param image The painted canvas to export.
 * @param filename Write the canvas to this file.
 */
void image_save( Image image, char *filename );

/**
 * Release image memory.
 *
 * @param image The allocated canvas memory.
 */
void image_close( Image image );

#endif

