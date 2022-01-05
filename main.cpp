#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <fmt/core.h>
#include <iostream>

bool quit = false;
SDL_Event gEvent{};
SDL_Window *gWindow{nullptr};
SDL_GLContext glRenderContext{nullptr};

int main(int, char **) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  // SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  int windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
  gWindow = SDL_CreateWindow("CoffeeGL", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, 800, 600, windowFlags);
  glRenderContext = SDL_GL_CreateContext(gWindow);
  if (glRenderContext == nullptr) {
    std::cout << "Unable to create SDL GL Context: " << SDL_GetError()
              << std::endl;
    return 1;
  }
  if (SDL_GL_MakeCurrent(gWindow, glRenderContext) != 0) {
    std::cout << "Unable to set current SDL GL Context: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // NOTE: enable V-Sync
  SDL_GL_SetSwapInterval(1);
  int w, h;
  SDL_GL_GetDrawableSize(gWindow, &w, &h);
  glViewport(0, 0, w, h);

  while (!quit) {
    while (SDL_PollEvent(&gEvent)) {
      if (gEvent.type == SDL_QUIT) {
        quit = true;
      }

      if (gEvent.type == SDL_KEYDOWN) {
        if (gEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          quit = true;
        }
      }

      if (gEvent.type == SDL_WINDOWEVENT) {
        if (gEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
          Sint32 newWidth = gEvent.window.data1;
          Sint32 newHeight = gEvent.window.data2;
          std::cout << fmt::format("Window resized: ({}, {})", newWidth,
                                   newHeight)
                    << std::endl;
          glViewport(0, 0, gEvent.window.data1, gEvent.window.data2);
        }
      }

      glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      SDL_GL_SwapWindow(gWindow);
    }
  }

  return 0;
}
