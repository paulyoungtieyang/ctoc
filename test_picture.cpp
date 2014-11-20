
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  picture image;
  image.matrix=NULL;
  image.n="gargouille.ppm";

  ppm_read_from_file(image);
  


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  picture image_bw;
  image_bw.w = image.w;
  image_bw.h = image.h; 
  image_bw.matrix = new u_char[3 * image.w * image.h]; 
  memcpy(image_bw.matrix, image.matrix, 3 * image_bw.w * image_bw.h * sizeof(*image_bw.matrix));
  

  // Desaturate image_bw
  ppm_desaturate(image_bw);

  // Write the desaturated image into "gargouille_BW.ppm"
  image_bw.n ="gargouille_BW.ppm" ;
  ppm_write_to_file(image_bw);

  // Free the desaturated image
  delete(image_bw.matrix);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  picture image_small;
  image_small.w = image.w;
  image_small.h = image.h;
  image_small.matrix = new u_char [3 * image_small.w * image_small.h];
  memcpy(image_small.matrix, image.matrix, 3 * image_small.w *image_small.h * sizeof(*image_small.matrix));

  // Shrink image_small size 2-fold
  ppm_shrink(image_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  image_small.n= "gargouille_small.ppm";
  ppm_write_to_file(image_small);

  // Free the not yet freed images
  delete(image.matrix);

  return 0;
}
