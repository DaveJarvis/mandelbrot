#include "image.h"

/**
 * Create a new image with the given width and height.
 */
Image image_open( int width, int height ) {
  for( int i = 0; i < sizeof( IMAGE_PALETTE ) / sizeof( int ); i++ ) {
    IMAGE_PALETTE[i] = -1;
  }

  return gdImageCreate( width, height );
}

/**
 * Create a new grayscale colour for the given image.
 */
int image_colour_grayscale( Image image, int s ) {
  if( IMAGE_PALETTE[ s ] == -1 ) {
    IMAGE_PALETTE[ s ] = gdImageColorAllocate( image, s, s, s );
  }

  return IMAGE_PALETTE[ s ];
}

/**
 * Draw a pixel on the image at the given coordinates with the given
 * saturation.
 */
void image_pixel( Image image, int x, int y, int saturation ) {
  int colour = image_colour_grayscale( image, saturation );

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

