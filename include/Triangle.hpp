#ifndef _triangle_hpp
#define _triangle_hpp

#include "OpenGLHeaders.hpp"

#include "DeltaTime.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Shader.hpp"
#include "Vertex.hpp"
#include <imgui.h>
#include <string>

class Triangle {
public:
  Triangle() {
    if (triangles.size() == 0) {
      glGenVertexArrays(1, &vertexArrayObject);
      glGenBuffers(1, &vertexBufferObject);

      shaderProg =
          new CoffeeGL::ShaderProgram("assets/shaders/hello-tri-uniform.vert",
                                      "assets/shaders/hello-tri-color.frag");

      vertices.resize(3);
      // 0 bytes offset
      vertices[0].position = glm::vec3{0.5f, -0.5f, 0.0f}; // 12 bytes
      vertices[0].color = glm::vec3{1.0f, 0.0f, 0.0f};     // 12 bytes
      // vertices[0].tex = glm::vec2{0.0f, 0.0f};             // 8 bytes
      // 24 bytes offset
      vertices[1].position = glm::vec3{-0.5f, -0.5f, 0.0f}; // 12 bytes
      vertices[1].color = glm::vec3{0.0f, 1.0f, 0.0f};      // 12 bytes
      // vertices[0].tex = glm::vec2{1.0f, 0.0f};              // 8 bytes
      // 24 bytes offset
      vertices[2].position = glm::vec3{0.0f, 0.5f, 0.0f}; // 12 bytes
      vertices[2].color = glm::vec3{0.0f, 0.0f, 1.0f};    // 12 bytes
      // vertices[0].tex = glm::vec2{0.5f, 1.0f};            // 8 bytes

      Init2();
    }

    id = ++uid;
    triangles.push_back(this);
  }

  ~Triangle() {
    if (triangles.size() == 1) {
      delete shaderProg; // last one out, turn off the lights.
      triangles.clear();
    }
  }

  void Init2() {
    std::cout << sizeof(Vertex) * vertices.size() << std::endl;

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void OnGui() {
    std::string windowName = "Triangle #" + std::to_string(id);
    ImGui::Begin(windowName.c_str());

    ImGui::SliderFloat("X Offset", &xOffset, -2.0f, 2.0f);
    ImGui::SliderFloat("Y Offset", &yOffset, -2.0f, 2.0f);

    ImGui::End();
  }

  void Draw() {

    shaderProg->Use();
    shaderProg->SetFloat("offset", xOffset, yOffset);

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }

  static void UI();

  static GLuint uid;
  static GLuint vertexArrayObject;
  static GLuint vertexBufferObject;
  static std::vector<Vertex> vertices;
  static CoffeeGL::ShaderProgram *shaderProg;
  static std::vector<Triangle *> triangles;

  GLuint id{0};
  float xOffset{0.0f};
  float yOffset{0.0f};
};

#endif
