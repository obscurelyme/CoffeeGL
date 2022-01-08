#ifndef _rectangle_hpp
#define _rectangle_hpp

#include "OpenGLHeaders.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include <vector>
#include "Image.hpp"
#include <string>
#include <tinyfiledialogs/tinyfiledialogs.h>
#include <array>
#include "DeltaTime.hpp"

class Rectangle {
public:
  Rectangle() {
    // shaderProg =
    //     new CoffeeGL::ShaderProgram("assets/shaders/hello-tri-color.vert",
    //                                 "assets/shaders/hello-tri-color.frag");

    shaderProg = new CoffeeGL::ShaderProgram("assets/shaders/standard.vert",
                                             "assets/shaders/standard.frag");

    img = new Image(imageFile);

    AssignVerticies();

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &elementBufferObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(vertexArrayObject);
    // Bind vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    // Bind index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2),
                          (void *)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2),
                          (void *)(sizeof(glm::vec3) * 2));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  ~Rectangle() { 
    delete shaderProg; 
    delete img; 
  }

  void OnGui() {
    std::string windowName = "Rectangle #" + std::to_string(1);
    ImGui::Begin(windowName.c_str());

    ImGui::SliderFloat("Texture Scale", &texScale, 1.0f, 10.0f);
    ImGui::SliderFloat("Texture xOffset", &xTexOffset, -10.0f, 10.0f);
    ImGui::SliderFloat("Texture yOffset", &yTexOffset, -10.0f, 10.0f);
    ImGui::InputFloat("Texture scroll speed", &scrollSpeed, 1.0f, 10.0f, "%.2f");

    ImGui::Checkbox("Y scrolling", &yScroll);
    ImGui::Checkbox("X scrolling", &xScroll);

    if (ImGui::BeginMenu("Shader Selection")) {
      if (ImGui::MenuItem("Vertex")) {
        // open file manager
        std::array<const char*, 1> filters{"*.vert"};
        char * newVertexShaderFilePath = tinyfd_openFileDialog("Select shader", nullptr, filters.size(), filters.data(), nullptr, 0);
        if (newVertexShaderFilePath != nullptr) {
          std::string originalFragmentShaderPath = shaderProg->FragmentShaderFilePath;
          delete shaderProg;
          shaderProg = new CoffeeGL::ShaderProgram(newVertexShaderFilePath, originalFragmentShaderPath, true);
        }
      }
      if (ImGui::MenuItem("Fragment")) {
        // open file manager
        std::array<const char*, 1> filters{"*.frag"};
        char * newFragmentShaderFilePath = tinyfd_openFileDialog("Select shader", nullptr, filters.size(), filters.data(), nullptr, 0);
        if (newFragmentShaderFilePath != nullptr) {
          std::string originalVertexShaderPath = shaderProg->VertexShaderFilePath;
          delete shaderProg;
          shaderProg = new CoffeeGL::ShaderProgram(originalVertexShaderPath, newFragmentShaderFilePath, true);
        }
      }

      if (ImGui::MenuItem("Reload Current Shaders")) {
        std::string originalVertexShaderPath = shaderProg->VertexShaderFilePath;
        std::string originalFragmentShaderPath = shaderProg->FragmentShaderFilePath;
        delete shaderProg;
        shaderProg = new CoffeeGL::ShaderProgram(originalVertexShaderPath, originalFragmentShaderPath, true);
      }
      ImGui::EndMenu();
    }

    ImGui::End();
  }

  void Draw() {    
    shaderProg->Use();
    // shaderProg->SetFloat("xOffset", 0.0f);
    // shaderProg->SetFloat("yOffset", 0.0f);
    shaderProg->SetFloat("texScale", texScale);
    if (xScroll) {
      position.x += scrollSpeed * CoffeeMaker::DeltaTime::Value();
      shaderProg->SetFloat("xTexOffset", position.x);
    }
    
    if (yScroll) {
      position.y += scrollSpeed * CoffeeMaker::DeltaTime::Value();
      shaderProg->SetFloat("yTexOffset", position.y);
    }
    

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, img->texture);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void AssignVerticies() {
    vertices.resize(4);
    indices.resize(6);

    vertices[0].position = glm::vec3{0.5f, 0.5f, 0.0f};
    vertices[0].color = glm::vec3{1.0f, 0.0f, 0.0f};
    vertices[0].tex = glm::vec2{1.0f, 1.0f};

    vertices[1].position = glm::vec3{0.5f, -0.5f, 0.0f};
    vertices[1].color = glm::vec3{0.0f, 1.0f, 0.0f};
    vertices[1].tex = glm::vec2{1.0f, 0.0f};

    vertices[2].position = glm::vec3{-0.5f, -0.5f, 0.0f};
    vertices[2].color = glm::vec3{0.0f, 0.0f, 1.0f};
    vertices[2].tex = glm::vec2{0.0f, 0.0f};

    vertices[3].position = glm::vec3{-0.5f, 0.5f, 0.0f};
    vertices[3].color = glm::vec3{1.0f, 1.0f, 1.0f};
    vertices[3].tex = glm::vec2{0.0f, 1.0f};

    indices = {0, 1, 3, 1, 2, 3};
  }

  GLuint vertexArrayObject;
  GLuint elementBufferObject;
  GLuint vertexBufferObject;
  std::vector<Vertex2> vertices{};
  std::vector<GLuint> indices{};
  CoffeeGL::ShaderProgram *shaderProg;
  Image* img;
  float texScale{1.0f};
  float xTexOffset{0.0f};
  float yTexOffset{0.0f};
  float scrollSpeed{50.0f};
  bool xScroll{false};
  bool yScroll{false};
  glm::vec2 position{0.0f};
  std::string imageFile{"assets/images/wall.jpeg"};
};

#endif
