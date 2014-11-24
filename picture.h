// This file must be added to the compilation process

class picture
{
 private:
  int width; //for width
  int height; //for height
  u_char* matrix; //for datas
  char* name; // for name

 public:
  // Constructors : default and copy
  picture(void);
  picture(const picture& old_picture);

  // Destructor
  ~picture(void);

  // Write the image contained in <data> (of size <width> * <height>)
  // into plain RGB ppm file <file>
  void ppm_write_to_file(void);
  
  // Read the image contained in plain RGB ppm file <file>
  // into <data> and set <width> and <height> accordingly
  void ppm_read_from_file(void);
  
  // Desaturate (transform to B&W) <image> (of size <width> * <height>)
  void ppm_desaturate(void);

  // Shrink image (of original size <width> * <height>) by factor <factor>
  // <width> and <height> are updated accordingly
  void ppm_shrink(int factor);

  // Accessors
  int getWidth(void) const;
  int getHeight(void) const;
  char* getName(void) const;
  u_char* getData(void) const;
  void setName(char* newName);

};





























