#ifndef _triangle_hpp
#define _triangle_hpp

#ifdef COFFEEMAKER_OS_WIN32
#include <glad/glad.h>
#else
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#endif

#include "DeltaTime.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Shader.hpp"
#include <imgui.h>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
};

class Triangle {
public:
  Triangle() {
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    shaderProg =
        new CoffeeGL::ShaderProgram("assets/shaders/hello-tri-color.vert",
                                    "assets/shaders/hello-tri-color.frag");

    vertices2.resize(3);
    // 0 bytes offset
    vertices2[0].position = glm::vec3{0.5f, -0.5f, 0.0f}; // 12 bytes
    vertices2[0].color = glm::vec3{1.0f, 0.0f, 0.0f};     // 12 bytes
    // 24 bytes offset
    vertices2[1].position = glm::vec3{-0.5f, -0.5f, 0.0f}; // 12 bytes
    vertices2[1].color = glm::vec3{0.0f, 1.0f, 0.0f};      // 12 bytes
    // 24 bytes offset
    vertices2[2].position = glm::vec3{0.0f, 0.5f, 0.0f}; // 12 bytes
    vertices2[2].color = glm::vec3{0.0f, 0.0f, 1.0f};    // 12 bytes

    Init2();
  }

  ~Triangle() { delete shaderProg; }

  void Init2() {
    std::cout << sizeof(float) * vertices3.size() << std::endl;
    std::cout << sizeof(Vertex) * vertices2.size() << std::endl;

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices2.size(),
                 vertices2.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(sizeof(Vertex) / 2));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void OnGui() {
    ImGui::Begin("Triangles");

    ImGui::SliderFloat("X Offset", &xOffset, -2.0f, 2.0f);

    ImGui::End();
  }

  void Draw() {
    // float timeValue = SDL_GetTicks() * 0.0016f;
    // float greenValue = sin(static_cast<float>(timeValue)) / 2 + 0.5f;
    // std::cout << CoffeeMaker::DeltaTime::Value() << " " << greenValue <<
    // std::endl; int vertexColorLocation = glGetUniformLocation(shaderProgram,
    // "customColor");

    shaderProg->Use();
    shaderProg->SetFloat("xOffset", xOffset);

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  GLuint vertexArrayObject;
  GLuint vertexBufferObject;
  std::vector<float> vertices{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                              0.0f,  0.0f,  0.5f, 0.0f};
  std::vector<float> vertices3{
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
  };

  std::vector<Vertex> vertices2{};

  CoffeeGL::ShaderProgram *shaderProg;
  float xOffset{0.0f};
};

#endif
