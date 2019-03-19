#ifndef __H_IMAGE
#define __H_IMAGE

#include <gd.h>

int IMAGE_PALETTE[255];

typedef gdImagePtr Image;

Image image_open( int width, int height );

/**
 * @param image Pointer to the image structure.
 * @param s Grayscale colour value.
 */
int image_colour_grayscale( Image image, int s );

void image_pixel( Image image, int x, int y, int colour );

void image_save( Image image, char *filename );

void image_close( Image image );

#endif

