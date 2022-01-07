#ifndef _coffeegl_vertex_hpp
#define _coffeegl_vertex_hpp

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
};

struct Vertex2 {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 tex;
};

#endif
