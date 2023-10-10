// Matrix implementation stuff!
#include "matrix/matrix4.h"

vectorf vectorf_new(float x, float y, float z, float w) {
    vectorf vec;
    vec.v[0] = x;
    vec.v[1] = y;
    vec.v[2] = z;
    vec.v[3] = w;

    return vec;
}

matrix matrix_identity() {
    matrix m = {.v = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
    return m;
}

matrix matrix_scale(float x, float y, float z) {
    matrix m = {.v = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    }};
    return m;
}

// Matrix operations {{{

matrix matrix_add(matrix* a, matrix* b) {
    matrix out;
    out.v[0] = a->v[0] + b->v[0];
    out.v[1] = a->v[1] + b->v[1];
    out.v[2] = a->v[2] + b->v[2];
    out.v[3] = a->v[3] + b->v[3];
    out.v[4] = a->v[4] + b->v[4];
    out.v[5] = a->v[5] + b->v[5];
    out.v[6] = a->v[6] + b->v[6];
    out.v[7] = a->v[7] + b->v[7];
    out.v[8] = a->v[8] + b->v[8];
    out.v[9] = a->v[9] + b->v[9];
    out.v[10] = a->v[10] + b->v[10];
    out.v[11] = a->v[11] + b->v[11];
    out.v[12] = a->v[12] + b->v[12];
    out.v[13] = a->v[13] + b->v[13];
    out.v[14] = a->v[14] + b->v[14];
    out.v[15] = a->v[15] + b->v[15];

    return out;
}

matrix matrix_sub(matrix *a, matrix *b) {
    matrix out;
    out.v[0] = a->v[0] - b->v[0];
    out.v[1] = a->v[1] - b->v[1];
    out.v[2] = a->v[2] - b->v[2];
    out.v[3] = a->v[3] - b->v[3];
    out.v[4] = a->v[4] - b->v[4];
    out.v[5] = a->v[5] - b->v[5];
    out.v[6] = a->v[6] - b->v[6];
    out.v[7] = a->v[7] - b->v[7];
    out.v[8] = a->v[8] - b->v[8];
    out.v[9] = a->v[9] - b->v[9];
    out.v[10] = a->v[10] - b->v[10];
    out.v[11] = a->v[11] - b->v[11];
    out.v[12] = a->v[12] - b->v[12];
    out.v[13] = a->v[13] - b->v[13];
    out.v[14] = a->v[14] - b->v[14];
    out.v[15] = a->v[15] - b->v[15];

    return out;
}

matrix matrix_div() {}

//}}}
