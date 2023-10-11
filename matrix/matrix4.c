// Matrix implementation stuff!
#include "matrix/matrix4.h"

vector4 vectorf_new(float x, float y, float z, float w) {
    vector4 vec;
    vec.v[0] = x;
    vec.v[1] = y;
    vec.v[2] = z;
    vec.v[3] = w;

    return vec;
}

matrix4 matrix_identity() {
    matrix4 m = MAT4_IDENTITY;
    return m;
}

matrix4 matrix_scale(float x, float y, float z) {
    matrix4 m = {.v = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    }};
    return m;
}

// Matrix operations {{{

matrix4 matrix_add(matrix4* a, matrix4* b) {
    matrix4 out;

    out.v[0][0] = a->v[0][0] + b->v[0][0];
    out.v[0][1] = a->v[0][1] + b->v[0][1];
    out.v[0][2] = a->v[0][2] + b->v[0][2];
    out.v[0][3] = a->v[0][3] + b->v[0][3];

    out.v[1][0] = a->v[1][0] + b->v[1][0];
    out.v[1][1] = a->v[1][1] + b->v[1][1];
    out.v[1][2] = a->v[1][2] + b->v[1][2];
    out.v[1][3] = a->v[1][3] + b->v[1][3];

    out.v[2][0] = a->v[2][0] + b->v[2][0];
    out.v[2][1] = a->v[2][1] + b->v[2][1];
    out.v[2][2] = a->v[2][2] + b->v[2][2];
    out.v[2][3] = a->v[2][3] + b->v[2][3];

    out.v[3][0] = a->v[3][0] + b->v[3][0];
    out.v[3][1] = a->v[3][1] + b->v[3][1];
    out.v[3][2] = a->v[3][2] + b->v[3][2];
    out.v[3][3] = a->v[3][3] + b->v[3][3];

    return out;
}

matrix4 matrix_sub(matrix4 *a, matrix4 *b) {
    matrix4 out;
    out.v[0][0] = a->v[0][0] - b->v[0][0];
    out.v[0][1] = a->v[0][1] - b->v[0][1];
    out.v[0][2] = a->v[0][2] - b->v[0][2];
    out.v[0][3] = a->v[0][3] - b->v[0][3];

    out.v[1][0] = a->v[1][0] - b->v[1][0];
    out.v[1][1] = a->v[1][1] - b->v[1][1];
    out.v[1][2] = a->v[1][2] - b->v[1][2];
    out.v[1][3] = a->v[1][3] - b->v[1][3];

    out.v[2][0] = a->v[2][0] - b->v[2][0];
    out.v[2][1] = a->v[2][1] - b->v[2][1];
    out.v[2][2] = a->v[2][2] - b->v[2][2];
    out.v[2][3] = a->v[2][3] - b->v[2][3];

    out.v[3][0] = a->v[3][0] - b->v[3][0];
    out.v[3][1] = a->v[3][1] - b->v[3][1];
    out.v[3][2] = a->v[3][2] - b->v[3][2];
    out.v[3][3] = a->v[3][3] - b->v[3][3];

    return out;
}

matrix4 matrix_mul(matrix4 *a, matrix4 *b) {
    // Declarations {{{
    float a00 = a->v[0][0],
        a01 = a->v[0][1],
        a02 = a->v[0][2],
        a03 = a->v[0][3],

        a10 = a->v[1][0],
        a11 = a->v[1][1],
        a12 = a->v[1][2],
        a13 = a->v[1][3],

        a20 = a->v[2][0],
        a21 = a->v[2][1],
        a22 = a->v[2][2],
        a23 = a->v[2][3],

        a30 = a->v[3][0],
        a31 = a->v[3][1],
        a32 = a->v[3][2],
        a33 = a->v[3][3];

    float b00 = b->v[0][0],
        b01 = b->v[0][1],
        b02 = b->v[0][2],
        b03 = b->v[0][3],

        b10 = b->v[1][0],
        b11 = b->v[1][1],
        b12 = b->v[1][2],
        b13 = b->v[1][3],

        b20 = b->v[2][0],
        b21 = b->v[2][1],
        b22 = b->v[2][2],
        b23 = b->v[2][3],

        b30 = b->v[3][0],
        b31 = b->v[3][1],
        b32 = b->v[3][2],
        b33 = b->v[3][3];
    // }}}

    matrix4 out;

    out.v[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
    out.v[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
    out.v[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
    out.v[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;

    out.v[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
    out.v[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
    out.v[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
    out.v[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;

    out.v[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
    out.v[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
    out.v[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
    out.v[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;

    out.v[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
    out.v[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
    out.v[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
    out.v[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;

    return out;
}

matrix4 matrix_div(matrix4 *a, matrix4 *b) {
    return (matrix4) {};
}

//}}}
