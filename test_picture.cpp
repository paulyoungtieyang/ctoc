
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "picture.h"

//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  picture image;
  image.setName("gargouille.ppm");
  image.ppm_read_from_file();
  


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  picture image_bw (image);
  
  
  // Desaturate image_bw
  image_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  image_bw.setName("gargouille_BW.ppm") ;
  image_bw.ppm_write_to_file();

  // Free the desaturated image
  


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  picture image_small(image);
  
  // Shrink image_small size 2-fold
  image_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  image_small.setName("gargouille_small.ppm");
  image_small.ppm_write_to_file();

  // Free the not yet freed images
  

  return 0;
}
