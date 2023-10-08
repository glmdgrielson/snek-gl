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

    // Vertex array object
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    if (glew_err != GLEW_OK) {
        fprintf(stderr, "GLEW failed: %s\n", glewGetErrorString(glew_err));
        return 1;
    }

    // The triangle we want to draw.
    const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // Create triangle
    GLuint vertex_buffer;
    // Make the buffer.
    glGenBuffers(1, &vertex_buffer);
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // Send the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

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
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
            0, // attribute?
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // not normalized
            0, // no stride, whatever that means
            (void*) 0 // fake our offset because we're responsible devs
        );

        //Actually draw!
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0); // What does that mean?
    }

    SDL_Quit();

    return 0;
}
