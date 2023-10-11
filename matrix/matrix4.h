#ifndef GLMD_MATRIX4_H
#define GLMD_MATRIX4_H

// A single column(?) of matrix data.
typedef struct vectorf {
    float v[4];
} vectorf;
typedef struct vectord {
    double v[4];
} vectord;

// A full four by four matrix.
typedef struct matrixf {
    float v[4][4];
} matrix4;

// vectorf new
vectorf vectorf_new(float x, float y, float z, float w);

const matrix4 MAT4_IDENTITY = {
    .v = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }
};

// Matrix constructor
matrix4 matrix_identity();
// Matrix scalar constructor. (Don't ask why there's no W here.)
matrix4 matrix_scale(float x, float y, float z);

// # Matrix operations {{{

// Matrix addition
matrix4* matrix_add(matrix4 *a, matrix4 *b, matrix4 *out);

// Matrix subtraction
matrix4* matrix_sub(matrix4 *a, matrix4 *b, matrix4 *out);

// Matrix/matrix multiplication.
matrix4* matrix_mul(matrix4 *a, matrix4 *b, matrix4 *out);

matrix4* matrix_div(matrix4 *a, matrix4 *b, matrix4 *out);

// }}}

#endif
