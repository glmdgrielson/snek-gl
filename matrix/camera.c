#include <math.h>

#include "camera.h"
#include "matrix/matrix4.h"

float deg2rad(float deg) {
    return deg * GLMD_PIf / 180.0f;
}

matrix4 perspective(float fov, float aspect, float nearZ, float farZ) {
    float tangent = tanf(fov * 0.5f);

    matrix4 out = {.v = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    out.v[0][0] = tangent / aspect;
    out.v[1][1] = tangent;
    out.v[2][2] = (nearZ + farZ) / (farZ - nearZ);
    out.v[2][3] = 1.0f;
    out.v[3][2] = (2.0f * farZ * nearZ) / (farZ - nearZ);

    return out;
}
