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
 * Pointer to region returned by this function must be closed using
 * image_region_close. The regions created by this function should be
 * non-overlapping so that individual threads can draw independently.
 *
 * @param image The image that was opened for drawing.
 * @param n The region index (0 through regions - 1).
 * @param regions The number of regions to create.
 */
struct region *image_region_open( Image image, int n, int regions ) {
  int x1 = 0, y1 = 0;
  int width = 0;
  int height = 0;
  struct region *region = malloc( sizeof( struct region ) );

  if( region != NULL ) {
    gdImageGetClip( image, &x1, &y1, &width, &height );

    int step_x = (int)round(1.0 * width / regions);
    int step_y = (int)round(1.0 * height / regions);

    region->x1 = step_x * n;
    region->y1 = 0;
    region->x2 = region->x1 + step_x;
    region->y2 = width;
  }

  return region;
}

/**
 * Closes region that was opened using image_region_open.
 */
void image_region_close( struct region *region ) {
  if( region != NULL ) {
    free( region );
  }
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

