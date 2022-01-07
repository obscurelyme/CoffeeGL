#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Image.hpp"
#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <iostream>

Image::Image(const std::string &fileName) : filename(fileName) {
  std::string fullFilePath = fmt::format("{}{}", SDL_GetBasePath(), filename);
  pixelData = stbi_load(fullFilePath.c_str(), &width, &height, &channels, 0);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT); // repeat along x-axis
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                  GL_REPEAT); // repeat along y-axis
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (pixelData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, pixelData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "failed to load texture: " << fullFilePath << std::endl;
  }

  glBindTexture(GL_TEXTURE_2D, 0); // unbind since we are now done.

  stbi_image_free(pixelData);
}

Image::~Image() {}
