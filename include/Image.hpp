#ifndef _image_hpp
#define _image_hpp

#include "OpenGLHeaders.hpp"
#include <string>

class Image {
public:
  explicit Image(const std::string &fileName);
  ~Image();

  int width{0};
  int height{0};
  int channels{0};
  unsigned char *pixelData{nullptr};
  std::string filename;
  GLuint texture;
};

#endif
