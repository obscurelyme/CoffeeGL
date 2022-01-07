#ifndef _shader_hpp
#define _shader_hpp

#ifdef COFFEEMAKER_OS_WIN32
#include <glad/glad.h>
#else
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#endif

#include <fstream>
#include <iostream>
#include <string>

namespace CoffeeGL {

class ShaderProgram {
public:
  ShaderProgram(const std::string &vertexShaderPath,
                const std::string &fragmentShaderPath, bool absolutePath = false);
  ~ShaderProgram();

  GLuint ShaderProgramID;

  void Load();
  void Use();
  void SetBool(const std::string &uniformName, bool value);
  void SetInt(const std::string &uniformName, int value);
  void SetFloat(const std::string &uniformName, float value);
  void SetFloat(const std::string& uniformName, float xValue, float yValue);
  void SetFloat(const std::string& uniformName, float xValue, float yValue, float zValue);

  GLuint vertexShader;
  GLuint fragmentShader;

  std::string vertexShaderSource;
  std::string fragmentShaderSource;

  std::string VertexShaderFilePath;
  std::string FragmentShaderFilePath;

private:
  void Compile();
  void Link();
  void UniformError(const std::string &uniformName);
};

} // namespace CoffeeGL

#endif
