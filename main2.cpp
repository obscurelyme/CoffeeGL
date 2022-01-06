#include <SDL2/SDL.h>
// #include <SDL2/SDL_opengl.h>
// #include <SDL2/SDL_opengl_glext.h>
#include <angle_gl.h>
#include <iostream>

int main(int, char **) {
  bool quit{false};
  SDL_Event event{};
  std::cout << "Hello, World!" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }
  int windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
  SDL_Window *window =
      SDL_CreateWindow("CoffeeGL", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 800, 600, windowFlags);

  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, context);

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    SDL_Delay(16);
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
