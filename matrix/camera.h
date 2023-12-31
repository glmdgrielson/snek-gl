// Camera nonsense because why not?
#ifndef GLMD_CAMERA_H
#define GLMD_CAMERA_H

#include "matrix4.h"
#include "vector3.h"

#define GLMD_PIf 3.14159265358979323846264338327950288f

float deg2rad(float deg);

/* This uses a right-handed perspective on a field going from negative
 * one to positive one because I BELIEVE that is what OpenGL defaults
 * to. Please let me know if this is incorrect.
 *
 * @param fov The field of view which is unfortunately in RADIANS.
 *     (Stupid unit thinks it gets to be a normal number...)
 */
matrix4 perspective(float fov, float aspect, float nearZ, float farZ);

matrix4 look_at(vector3 eye, vector3 center, vector3 up);

#endif
