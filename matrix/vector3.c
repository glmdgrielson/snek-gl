#include <math.h>

#include "vector3.h"

vector3 vec3_add(vector3* a, vector3* b) {
    vector3 out;

    out.v[0] = a->v[0] + b->v[0];
    out.v[1] = a->v[1] + b->v[1];
    out.v[2] = a->v[2] + b->v[2];

    return out;
}

vector3 vec3_sub(vector3* a, vector3* b) {
    vector3 out;

    out.v[0] = a->v[0] - b->v[0];
    out.v[1] = a->v[1] - b->v[1];
    out.v[2] = a->v[2] - b->v[2];

    return out;
}

vector3 vec3_scale(vector3 *a, float scalar) {
    vector3 out = {.v = {
        a->v[0] * scalar,
        a->v[1] * scalar,
        a->v[2] * scalar,
    }};

    return out;
}

float vec3_norm(vector3 *vec) {
    return sqrtf(vec->v[0] *vec->v[0] + vec->v[1] * vec->v[1] + vec->v[2] * vec->v[2]);
}

void vec3_normalize(vector3 *vec) {
    float norm = vec3_norm(vec);

    if (norm == 0.0f) {
        vec->v[0] = 0.0f;
        vec->v[1] = 0.0f;
        vec->v[2] = 0.0f;
        return;
    }

    *vec = vec3_scale(vec, 1.0 / norm);
}
