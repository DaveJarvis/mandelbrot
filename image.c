#include "image.h"

Image image_open( int width, int height ) {
  for( int i = 0; i < sizeof( IMAGE_PALETTE ) / sizeof( int ); i++ ) {
    IMAGE_PALETTE[i] = -1;
  }

  return gdImageCreate( width, height );
}

struct region *image_region_open( Image image, int n, int regions ) {
  int x1 = 0;
  int y1 = 0;
  int width = 0;
  int height = 0;
  struct region *region = memory_open( sizeof( struct region ) );

  if( region != NULL ) {
    gdImageGetClip( image, &x1, &y1, &width, &height );

    int step_x = (int)round( 1.0 * width / regions );
    int step_y = (int)round( 1.0 * height / regions );

    region->x1 = step_x * n;
    region->y1 = 0;
    region->x2 = region->x1 + step_x;
    region->y2 = height;
  }

  return region;
}

void image_region_close( struct region *region ) {
  if( region != NULL ) {
    memory_close( region );
  }
}

int image_colour_grayscale( Image image, int s ) {
  if( IMAGE_PALETTE[ s ] == -1 ) {
    IMAGE_PALETTE[ s ] = gdImageColorAllocate( image, s, s, s );
  }

  return IMAGE_PALETTE[ s ];
}

void image_pixel( Image image, int x, int y, int saturation ) {
  int colour = image_colour_grayscale( image, saturation );

  gdImageSetPixel( image, x, y, colour );
}

void image_save( Image image, char *filename ) {
  FILE *fout = fopen( filename, "wb" );

  if( fout != NULL ) {
    gdImagePng( image, fout );
    
    fclose( fout );
  }
}

void image_close( Image image ) {
  if( image != NULL ) {
    gdImageDestroy( image );
  }
}

