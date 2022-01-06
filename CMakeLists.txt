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
# find_package(unofficial-angle CONFIG REQUIRED)
# find_package(ZLIB REQUIRED)

add_executable(CoffeeGL main.cpp)

add_compile_definitions(GLM_FORCE_RADIANS)
add_compile_definitions(GL_GLEXT_PROTOTYPES)

if(OPENGL_FOUND)
  message(STATUS "OpenGL Libs: ${OPENGL_LIBRARIES}\nOpenGL Include Dirs: ${OPENGL_INCLUDE_DIR}")
  target_link_libraries(CoffeeGL PRIVATE ${OPENGL_LIBRARIES})
  # target_include_directories(CoffeeGL PRIVATE ${OPENGL_INCLUDE_DIR})
else()
  message(FATAL "Cannot find OpenGL library")
endif()

# SDL2
if(WIN32)
  target_link_libraries(CoffeeGL PRIVATE SDL2::SDL2 SDL2::SDL2main)
else()
  target_link_libraries(CoffeeGL PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
endif()

target_link_libraries(CoffeeGL PRIVATE
  fmt::fmt-header-only
  glm::glm
  imgui::imgui
  # unofficial::angle::libEGL
  # unofficial::angle::libANGLE
  # unofficial::angle::libGLESv2
  # unofficial::angle::angle_common
)
target_include_directories(CoffeeGL PRIVATE include)

if(APPLE)
  add_compile_definitions(COFFEEMAKER_OS_APPLE)
  add_compile_definitions(GL_SILENCE_DEPRECATION)
elseif(WIN32)
  add_compile_definitions(COFFEEMAKER_OS_WIN32)
else()
  add_compile_definitions(COFFEEMAKER_OS_LINUX)
endif()
