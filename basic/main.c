// C Standard library
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// SDL things
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_keycode.h>

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

int main(int argc, char** argv) {
    // Start up SDL.
    int sdl_err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (sdl_err != 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Set up the window.
    uint32_t window_flags = SDL_WINDOW_OPENGL;
    SDL_Window *window = SDL_CreateWindow("OpenGL Test?", 0, 0, WINDOW_HEIGHT, WINDOW_WIDTH, window_flags);

    if (window == NULL) {
        fprintf(stderr, "Window did not initialize.");
        return 1;
    }

    // GL stuff.
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    GLenum glew_err = glewInit();

    if (glew_err != GLEW_OK) {
        fprintf(stderr, "GLEW failed: %s\n", glewGetErrorString(glew_err));
        return 1;
    }

    bool running = 1;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();

    return 0;
}
