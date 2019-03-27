#include "image.h"

#include "colours.h"
#include "memory.h"

Image image_open( int width, int height ) {
  return gdImageCreateTrueColor( width, height );
}

struct region *image_region_open( Image image, int n, int regions ) {
  int x1 = 0;
  int y1 = 0;
  int width = 0;
  int height = 0;
  struct region *region = memory_open( sizeof( struct region ) );

  if( region != NULL ) {
    // The parameters could have been passed in, but deriving them keeps the
    // function prototype simpler.
    gdImageGetClip( image, &x1, &y1, &width, &height );

    // Determine the pixel area that each thread is responsible for rendering.
    int step_size = width / regions;
    int remainder = width - (step_size * regions);

    region->x1 = step_size * n;

    // Determine whether extra work is required by the last thread.
    if( n < remainder ) {
      // If so, lengthen the chunk and start from the corrected position.
      step_size++;
      region->x1 += n;
    }
    else {
      // If not, start from the corrected position.
      region->x1 += remainder;
    }

    // Will not exceed the image size.
    region->x2 = region->x1 + step_size;

    region->y1 = 0;
    region->y2 = height;
  }

  return region;
}

void image_region_close( struct region *region ) {
  memory_close( region );
}

void image_pixel( Image image, int x, int y, int r, int g, int b ) {
  // Convert three 8-bit colours to a single 24-bit ("true") colour.
  int colour = (r << 16) | (g << 8) | b;

  gdImageSetPixel( image, x, y, colour );
}

void image_save( Image image, char *filename ) {
  FILE *fout = fopen( filename, "wb" );

  if( fout != NULL ) {
    // Persist the image.
    gdImagePng( image, fout );

    fclose( fout );
  }
}

void image_close( Image image ) {
  if( image != NULL ) {
    gdImageDestroy( image );
  }
}

