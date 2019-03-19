#ifndef __H_IMAGE
#define __H_IMAGE

#include <gd.h>

#define IMAGE_WIDTH (256)
#define IMAGE_HEIGHT (160)

#define IMAGE_SCALE (1)

typedef gdImagePtr Image;

Image image_open( int width, int height );

int image_colour( Image image, int r, int g, int b );

void image_pixel( Image image, int x, int y, int colour );

void image_save( Image image, char *filename );

void image_close( Image image );

#endif

