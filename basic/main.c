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
    uint32_t window_flags = SDL_WINDOW_OPENGL;
    SDL_Window *window = SDL_CreateWindow("OpenGL Test?", 0, 0, WINDOW_HEIGHT, WINDOW_WIDTH, window_flags);

    if (window == NULL) {
        fprintf(stderr, "Window did not initialize.");
        return -1;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW failed: %s\n", glewGetErrorString(err));
        return -1;
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
    }

    SDL_GL_SwapWindow(window);

    return 0;
}
