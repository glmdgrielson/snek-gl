#ifndef GLMD_VECTOR3
#define GLMD_VECTOR3

typedef struct vector3 {
    float v[3];
} vector3;

// Basic operations {{{

vector3 vec3_add(vector3 *a, vector3 *b);

vector3 vec3_sub(vector3 *a, vector3 *b);

vector3 vec3_scale(vector3 *a, float scalar);

// }}}

// Normalization {{{

vector3 vec3_norm();

vector3 vec3_normalize();

// }}}

#endif
