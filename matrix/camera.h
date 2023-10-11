// Camera nonsense because why not?
#ifndef GLMD_CAMERA_H
#define GLMD_CAMERA_H

#include "matrix4.h"

const float GLMD_PIf = 3.14159265358979323846264338327950288f;

float deg2rad(float deg);

/* This uses a right-handed perspective on a field going from negative
 * one to positive one because I BELIEVE that is what OpenGL defaults
 * to. Please let me know if this is incorrect.
 *
 * @param fov The field of view which is unfortunately in RADIANS.
 *     (Stupid unit thinks it gets to be a normal number...)
 */
matrix4 perspective(float fov, float aspect, float nearZ, float farZ);

#endif
