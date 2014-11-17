
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//============================================================================
//                           Function declarations
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(int width, int height, u_char* data, char* file);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(int *width, int *height, u_char** data, char* file);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(u_char* image, int width, int height);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(u_char** image, int *width, int *height, int factor);


//============================================================================
//                          Struct declarations & definitions
//                      (struct must be declared before main : memory space needed MUST be known)
//============================================================================
struct picture
{
  int w; //for width
  int h; //for height
  u_char* matrix; //for datas
  char* n; // for name
}; 



//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  
  u_char* image = NULL;
  int width;
  int height;
  char* ppm_input="gargouille.ppm";
  ppm_read_from_file(&width, &height, &image, ppm_input);
  


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  struct picture image_bw;
  image_bw.w = width;
  image_bw.h = height; 
  image_bw.matrix = (u_char*) malloc (3 * image_bw.w * image_bw.h * sizeof(u_char)); 
  
  memcpy(image_bw.matrix, image, 3 * width * height * sizeof(*image_bw.matrix));


  // Desaturate image_bw
  ppm_desaturate(image_bw.matrix, width, height);

  // Write the desaturated image into "gargouille_BW.ppm"
  image_bw.n ="gargouille_BW.ppm" ;
  ppm_write_to_file(width, height, image_bw.matrix,image_bw.n);

  // Free the desaturated image
  free(image_bw.matrix);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  struct picture image_small;
  image_small.w = width;
  image_small.h = height;
  image_small.matrix = (u_char*) malloc(3 * image_small.w * image_small.h * sizeof(u_char));
  memcpy(image_small.matrix, image, 3 * image_small.w *image_small.h * sizeof(*image_small.matrix));

  // Shrink image_small size 2-fold
  ppm_shrink(&image_small.matrix, &image_small.w, &image_small.h, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  image_small.n= "gargouille_small.ppm";
  ppm_write_to_file( image_small.w,image_small.h, image_small.matrix,image_small.n);

  // Free the not yet freed images
  free(image);
  free(image_small.matrix);

  return 0;
}





//============================================================================
//                           Function definitions
//============================================================================
void ppm_write_to_file(int width, int height, u_char* data, char* name)
{
  //Open new gargouille BW file
  FILE* file = fopen(name, "wb"); 

  // Write header
  fprintf(file, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(data, 3, width*height, file);

  // Close file
  fclose(file);  
}

void ppm_read_from_file(int *width, int *height, u_char** data, char* name)
{
  //Open gargouille file
  FILE* file =  fopen(name, "rb");
 
 // Read file header
  fscanf(file, "P6\n%d %d\n255\n", width, height);

  // Allocate memory according to width and height
  *data = (u_char*) malloc(3 * (*width) * (*height) * sizeof(**data));

  // Read the actual image data
  fread(*data, 3, (*width) * (*height), file);

  // Close file
  fclose(file);  
}

void ppm_desaturate(u_char* image, int width, int height)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < width ; x++)
  {
    for (y = 0 ; y < height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += image[ 3 * (y * width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&image[3 * (y * width + x)], grey_lvl, 3);
    }
  }
}

void ppm_shrink(u_char** image, int *width, int *height, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (*width) / factor;
  int new_height  = (*height) / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (*width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (*width) + dx);

          // Accumulate RGB values
          red   += (*image)[i0+delta_i];
          green += (*image)[i0+delta_i+1];
          blue  += (*image)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  *width  = new_width;
  *height = new_height;

  // Update image
  free(*image);
  *image = new_image;
}


//==========================================================================
//                              Struct definition
//==========================================================================




































