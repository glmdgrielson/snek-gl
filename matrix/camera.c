#include <math.h>

#include "camera.h"
#include "matrix/matrix4.h"
#include "vector3.h"

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

// I wish I understood any of why this algorithm does what it does.
matrix4 look_at(vector3 eye, vector3 center, vector3 up) {
    matrix4 out;
    vector3 f, s, u;

    f = vec3_sub(&center, &eye);
    vec3_normalize(&f);

    s = vec3_cross_norm(&f, &up);
    u = vec3_cross(&s, &f);

    out.v[0][0] = s.v[0];
    out.v[0][1] = u.v[0];
    out.v[0][2] = -f.v[0];

    out.v[1][0] = s.v[1];
    out.v[1][1] = u.v[1];
    out.v[1][2] = -f.v[1];

    out.v[2][0] = s.v[2];
    out.v[2][1] = u.v[2];
    out.v[2][2] = -f.v[2];

    out.v[3][0] = -vec3_dot(&s, &eye);
    out.v[3][1] = -vec3_dot(&u, &eye);
    out.v[3][2] = vec3_dot(&f, &eye);

    out.v[0][3] = 0.0f;
    out.v[1][3] = 0.0f;
    out.v[2][3] = 0.0f;
    out.v[3][3] = 1.0f;

    return out;
}
