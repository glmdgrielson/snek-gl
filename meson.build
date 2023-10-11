project('snek-gl', 'c')

sdl = dependency('sdl2')
gl = dependency('gl')
glew = dependency('glew')

# Stupid C making me need this...
lm = meson.get_compiler('c').find_library('m', required : false)

executable(
    'basic', 'basic/main.c',
    dependencies : [sdl, gl, glew])

matrix_src = [
    'matrix/matrix4.c',
    'matrix/vector3.c',
    'matrix/camera.c'
]

executable(
    'matrix', 'matrix/main.c',
    dependencies: [sdl, gl, glew, lm],
    sources: matrix_src)
