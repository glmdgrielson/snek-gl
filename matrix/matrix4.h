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
    float v[16];
} matrix;

// vectorf new
vectorf vectorf_new(float x, float y, float z, float w);

// Matrix constructor
matrix matrix_identity();
// Matrix scalar constructor. (Don't ask why there's no W here.)
matrix matrix_scale(float x, float y, float z);

// # Matrix operations {{{

// Matrix addition
matrix matrix_add(matrix *a, matrix *b);

// Matrix subtraction
matrix matrix_sub(matrix *a, matrix *b);

// }}}

#endif
