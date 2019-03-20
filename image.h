#ifndef __H_IMAGE
#define __H_IMAGE

#include <math.h>
#include <gd.h>

#include "memory.h"

int IMAGE_PALETTE[255];

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
 * @param width The number of pixels from top to bottom.
 */
Image image_open( int width, int height );

/**
 * Opens an image region boundary.
 *
 * @param n The region number.
 * @param regions The number of regions.
 */
struct region *image_region_open( Image image, int n, int regions );

/**
 * Releases memory set aside for an image region boundary.
 *
 * @param region The region to deallocate.
 */
void image_region_close( struct region *region );

/**
 * @param image Pointer to the image structure.
 * @param s Grayscale colour value.
 */
int image_colour_grayscale( Image image, int s );

void image_pixel( Image image, int x, int y, int colour );

void image_save( Image image, char *filename );

void image_close( Image image );

#endif

