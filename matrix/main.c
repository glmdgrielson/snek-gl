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

#include "matrix4.h"
#include "vector3.h"
#include "camera.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

const char* VERTEX_SHADER =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertex_position;\n"
    "uniform mat4 mvp;\n"
    "void main() {\n"
    "   gl_Position = mvp * vec4(vertex_position, 1);\n"
    "}";

const char* FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec3 color;\n"
    "void main() {\n"
    "   color = vec3(0.73, 0.86, 0.93); // #BADBED\n"
    "}";

GLuint compile_shader(const char *fragment, const char* vertex) {
    // Error handling
    GLint result = GL_FALSE;
    GLint log_length = 0;

    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile the vertex shader.
    glShaderSource(vertex_id, 1, &vertex, NULL);
    glCompileShader(vertex_id);

    // Error check the vertex shader.
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar error_msg[1024];
        glGetShaderInfoLog(vertex_id, log_length, NULL, error_msg);
        fprintf(stderr, "%s\n", error_msg);
    }

    // Compile the fragment shader.
    glShaderSource(fragment_id, 1, &fragment, NULL);
    glCompileShader(fragment_id);

    // Error check the fragment shader.
    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar error_msg[1024];
        glGetShaderInfoLog(fragment_id, log_length, NULL, error_msg);
        fprintf(stderr, "%s\n", error_msg);
    }

    // Make the program.
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);

    // Check that linking succeeded.
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar error_msg[1024];
        glGetProgramInfoLog(program_id, log_length, NULL, error_msg);
        fprintf(stderr, "%s\n", error_msg);
    }

    // Cleanup the shaders.
    glDetachShader(program_id, vertex_id);
    glDetachShader(program_id, fragment_id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return program_id;
}

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

    matrix4 projection = perspective(deg2rad(45.0f), (float)WINDOW_WIDTH /(float)WINDOW_HEIGHT, 0.0f, 100.0f);

    vector3 center = {{4, 3, 3}};
    vector3 eye = {{0, 0, 0}};
    vector3 up = {{0, 1, 0}};
    matrix4 view = look_at(eye, center, up);

    matrix4 model = matrix_identity();

    matrix4 mvp = matrix_mul(&projection, &view);
    mvp = matrix_mul(&mvp, &model);

    // matrix4 view = look_at({.v = {4, 3, 3}}, , )

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

    GLuint program_id = compile_shader(FRAGMENT_SHADER, VERTEX_SHADER);

    GLuint matrix_id = glGetUniformLocation(program_id, "mvp");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp.v[0][0]);

        //Actually draw!
        glUseProgram(program_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0); // What does that mean?
    }

    SDL_Quit();

    return 0;
}
