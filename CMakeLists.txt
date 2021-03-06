cmake_minimum_required(VERSION 3.18.0)

set(VCPKG_MANIFEST_MODE TRUE)
set(C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(CoffeeGL VERSION 0.1.0)

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")
find_package(tinyfiledialogs CONFIG REQUIRED)

if(WIN32)
  find_package(glad CONFIG REQUIRED)
else()
  add_compile_definitions(GL_GLEXT_PROTOTYPES)
endif()

add_executable(CoffeeGL main.cpp DeltaTime.cpp Shader.cpp Image.cpp Triangle.cpp)

add_compile_definitions(GLM_FORCE_RADIANS)

if(OPENGL_FOUND)
  message(STATUS "OpenGL Libs: ${OPENGL_LIBRARIES}\nOpenGL Include Dirs: ${OPENGL_INCLUDE_DIR}")
  target_link_libraries(CoffeeGL PRIVATE ${OPENGL_LIBRARIES})
  target_include_directories(CoffeeGL PRIVATE ${OPENGL_INCLUDE_DIR})
else()
  message(FATAL "Cannot find OpenGL library")
endif()

# SDL2 + GLAD
if(WIN32)
  target_link_libraries(CoffeeGL PRIVATE glad::glad SDL2::SDL2 SDL2::SDL2main)
else()
  target_link_libraries(CoffeeGL PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
endif()

target_link_libraries(CoffeeGL PRIVATE
  fmt::fmt-header-only
  glm::glm
  imgui::imgui
  tinyfiledialogs::tinyfiledialogs
)
target_include_directories(CoffeeGL PRIVATE include ${STB_INCLUDE_DIRS})

if(APPLE)
  add_compile_definitions(COFFEEMAKER_OS_APPLE)
  add_compile_definitions(GL_SILENCE_DEPRECATION)
elseif(WIN32)
  add_compile_definitions(COFFEEMAKER_OS_WIN32)
else()
  add_compile_definitions(COFFEEMAKER_OS_LINUX)
endif()
