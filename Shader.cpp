#include "Shader.hpp"
#include <fmt/core.h>
#include <SDL2/SDL.h>
#include <vector>
#include <sstream>

CoffeeGL::ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  std::string fullFilePathVertex = fmt::format("{}{}", SDL_GetBasePath(), vertexShaderPath);
  std::string fullFilePathFragment = fmt::format("{}{}", SDL_GetBasePath(), fragmentShaderPath);

  std::ifstream vertexShaderfile;
  std::ifstream fragmentShaderfile;

  vertexShaderfile.open(fullFilePathVertex);
  fragmentShaderfile.open(fullFilePathFragment);

  if (!vertexShaderfile.is_open()) {
    std::cerr << fmt::format("Could not open shader file {}", fullFilePathVertex) << std::endl;
    exit(2);
  }
  if (!fragmentShaderfile.is_open()) {
    std::cerr << fmt::format("Could not open shader file {}", fullFilePathFragment) << std::endl;
    exit(2);
  }

  std::stringstream vShaderStream, fShaderStream;
  
  vShaderStream << vertexShaderfile.rdbuf();
  fShaderStream << fragmentShaderfile.rdbuf();

  vertexShaderfile.close();
  fragmentShaderfile.close();

  vertexShaderSource = vShaderStream.str();
  fragmentShaderSource = fShaderStream.str();

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  ShaderProgramID = glCreateProgram();
  Compile();
  Link();
}

CoffeeGL::ShaderProgram::~ShaderProgram() {}

void CoffeeGL::ShaderProgram::Use() {
  glUseProgram(ShaderProgramID);
}

void CoffeeGL::ShaderProgram::SetBool(const std::string& uniformName, bool value) {
  GLint uniformLocation = glGetUniformLocation(ShaderProgramID, uniformName.c_str());
  glUniform1i(uniformLocation, value);
}

void CoffeeGL::ShaderProgram::SetInt(const std::string& uniformName, int value) {
  GLint uniformLocation = glGetUniformLocation(ShaderProgramID, uniformName.c_str());
  glUniform1i(uniformLocation, value);
}

void CoffeeGL::ShaderProgram::SetFloat(const std::string& uniformName, float value) {
  GLint uniformLocation = glGetUniformLocation(ShaderProgramID, uniformName.c_str());
  glUniform1f(uniformLocation, value);
}

void CoffeeGL::ShaderProgram::Compile() {
  int success;
  char infoLog[512];

  const char * gg = vertexShaderSource.c_str();
  glShaderSource(vertexShader, 1, &gg, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    exit(1);
  }

  const char * ff = fragmentShaderSource.c_str();
  glShaderSource(fragmentShader, 1, &ff, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    exit(1);
  }
}

void CoffeeGL::ShaderProgram::Link() {
  int success;
  char infoLog[512];

  glAttachShader(ShaderProgramID, vertexShader);
  glAttachShader(ShaderProgramID, fragmentShader);
  glLinkProgram(ShaderProgramID);
  glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINK::FAILED\n" << infoLog << std::endl;
    exit(1);
  }
  // no longer need shaders anymore after linking
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}