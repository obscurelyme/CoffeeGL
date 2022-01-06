#include "Triangle.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <iostream>

bool quit = false;
SDL_Event gEvent{};
SDL_Window *gWindow{nullptr};
SDL_GLContext glRenderContext{nullptr};
bool opened = true;

int viewportWidth, viewportHeight;

int main(int, char **) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

#ifdef COFFEEMAKER_OS_APPLE
  const char *glsl_version = "#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#else
  const char *glsl_version = "#version 130";
#endif
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

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
  if (SDL_GL_SetSwapInterval(1) != 0) {
    std::cout << "Warning, unable to set OpenGL to V-Sync: " << SDL_GetError()
              << std::endl;
  }
  SDL_GL_GetDrawableSize(gWindow, &viewportWidth, &viewportHeight);
  glViewport(0, 0, viewportWidth, viewportHeight);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  ImFont *robotoFont{nullptr};
  robotoFont = io.Fonts->AddFontFromFileTTF(
      fmt::format("{}{}", SDL_GetBasePath(), "/assets/fonts/Roboto.ttf")
          .c_str(),
      18);
  if (robotoFont == nullptr) {
    std::cout << "Could not load Roboto Font" << std::endl;
    return 2;
  }
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForOpenGL(gWindow, glRenderContext);
  ImGui_ImplOpenGL3_Init(glsl_version);

  Triangle tri;

  while (!quit) {
    while (SDL_PollEvent(&gEvent)) {
      ImGui_ImplSDL2_ProcessEvent(&gEvent);

      if (gEvent.type == SDL_QUIT) {
        quit = true;
      }

      if (gEvent.type == SDL_KEYDOWN) {
        if (gEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          quit = true;
        }
      }

      if (gEvent.type == SDL_WINDOWEVENT) {
        if (gEvent.window.event == SDL_WINDOWEVENT_SHOWN) {
          SDL_GL_GetDrawableSize(gWindow, &viewportWidth, &viewportHeight);
          glViewport(0, 0, viewportWidth, viewportHeight);
          std::cout << fmt::format("Window shown: ({}, {})", viewportWidth,
                                   viewportHeight)
                    << std::endl;
        }
        if (gEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
          SDL_GL_GetDrawableSize(gWindow, &viewportWidth, &viewportHeight);
          glViewport(0, 0, viewportWidth, viewportHeight);
          std::cout << fmt::format("Window resized: ({}, {})", viewportWidth,
                                   viewportHeight)
                    << std::endl;
        }
      }

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL2_NewFrame();
      ImGui::NewFrame();

      ImGui::ShowDemoWindow();

      ImGui::Render();

      glViewport(0, 0, viewportWidth, viewportHeight);
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      tri.Draw();

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      SDL_GL_SwapWindow(gWindow);

      SDL_Delay(16);
    }
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(glRenderContext);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();

  return 0;
}
