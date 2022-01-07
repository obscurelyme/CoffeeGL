#include "Triangle.hpp"

GLuint Triangle::uid{0};
GLuint Triangle::vertexArrayObject;
GLuint Triangle::vertexBufferObject;
std::vector<Vertex> Triangle::vertices{};
CoffeeGL::ShaderProgram *Triangle::shaderProg{nullptr};
std::vector<Triangle *> Triangle::triangles{};

void Triangle::UI() {
  for (auto tri : triangles) {
    tri->OnGui();
  }
}
