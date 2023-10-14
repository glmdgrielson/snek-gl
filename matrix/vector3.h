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

float vec3_norm(vector3 *vec);

// Normalize a vector-3 IN PLACE.
void vec3_normalize(vector3 *vec);

// }}}

#endif
