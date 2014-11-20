// This file must be added to the compilation process
// g++ compilation is compulsory due to pass by reference


//============================================================================
//                          Struct declarations & definitions
//                      (struct must be declared before main : memory space needed MUST be known)
//============================================================================
typedef struct
{
  int w; //for width
  int h; //for height
  u_char* matrix; //for datas
  char* n; // for name
} picture; 




//============================================================================
//                           Function declarations
//============================================================================

// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(picture image);



// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(picture& image);



// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(picture image);



// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(picture& image, int factor);










