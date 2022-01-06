#ifndef _shader_hpp
#define _shader_hpp

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <iostream>
#include <string>

namespace CoffeeGL {

  class ShaderProgram {
    public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~ShaderProgram();

    GLuint ShaderProgramID;
    
    void Use();
    void SetBool(const std::string& uniformName, bool value);
    void SetInt(const std::string& uniformName, int value);
    void SetFloat(const std::string& uniformName, float value);
    
    GLuint vertexShader;
    GLuint fragmentShader;
    
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    private:
    void Compile();
    void Link();
  };

}

#endif