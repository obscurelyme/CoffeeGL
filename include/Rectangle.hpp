#ifndef _rectangle_hpp
#define _rectangle_hpp

#include "OpenGLHeaders.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include <vector>

class Rectangle {
public:
  Rectangle() {
    shaderProg =
        new CoffeeGL::ShaderProgram("assets/shaders/hello-tri-color.vert",
                                    "assets/shaders/hello-tri-color.frag");

    vertices.resize(4);
    indices.resize(6);

    vertices[0].position = glm::vec3{0.5f, 0.5f, 0.0f};
    vertices[0].color = glm::vec3{1.0f, 0.0f, 0.0f};
    vertices[1].position = glm::vec3{0.5f, -0.5f, 0.0f};
    vertices[1].color = glm::vec3{0.0f, 1.0f, 0.0f};
    vertices[2].position = glm::vec3{-0.5f, -0.5f, 0.0f};
    vertices[2].color = glm::vec3{0.0f, 0.0f, 1.0f};
    vertices[3].position = glm::vec3{-0.5f, 0.5f, 0.0f};
    vertices[3].color = glm::vec3{1.0f, 1.0f, 1.0f};

    indices = {0, 1, 3, 1, 2, 3};

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &elementBufferObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(vertexArrayObject);
    // Bind vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    // Bind index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  ~Rectangle() { delete shaderProg; }

  void Draw() {
    shaderProg->Use();
    // shaderProg->SetFloat("xOffset", 0.0f);
    // shaderProg->SetFloat("yOffset", 0.0f);

    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  GLuint vertexArrayObject;
  GLuint elementBufferObject;
  GLuint vertexBufferObject;
  std::vector<Vertex> vertices{};
  std::vector<GLuint> indices{};
  CoffeeGL::ShaderProgram *shaderProg;
};

#endif
