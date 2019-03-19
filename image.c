#include "image.h"

/**
 * Create a new image with the given width and height.
 */
Image image_open( int width, int height ) {
  return gdImageCreate( width, height );
}

/**
 * Create a new RGB colour for the given image.
 */
int image_colour( Image image, int r, int g, int b ) {
  return gdImageColorAllocate( image, r, g, b );
}

/**
 * Draw a pixel on the image at the given coordinates with the given
 * colour.
 */
void image_pixel( Image image, int x, int y, int colour ) {
  gdImageSetPixel( image, x, y, colour );
}

/**
 * Export the given image to a specified file.
 */
void image_save( Image image, char *filename ) {
  FILE *fout = fopen( filename, "wb" );

  if( fout != NULL ) {
    gdImagePng( image, fout );
    
    fclose( fout );
  }
}

/**
 * Release the memory for the image.
 */
void image_close( Image image ) {
  gdImageDestroy( image );
}

