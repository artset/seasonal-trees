#version 400 core

in vec3 position;
in vec3 normal;

out vec3 fragPos;
out vec3 fragNorm;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;


float triangleNoise(float x, float frac) {
        return abs(fract(x)-frac);
}

vec4 displacementMap(vec4 pos) {
    float rad = sqrt(pow(pos.z, 2) + pow(pos.x, 2));

    vec4 newPos = pos;
    newPos.y = triangleNoise(newPos.x, rad) + newPos.y;


    return newPos;
}

vec4 objectNormalToWorld(mat4 trans, vec4 normal) {
    mat3 m = mat3(trans);
    m = inverse(transpose(m));
    vec3 res = m * vec3(normal.xyz);
    return normalize(vec4(res, 0.f));
}


void main(void) {
    vec4 newPos = vec4(position, 1);
    newPos = displacementMap(newPos);

    fragPos = (model * newPos).xyz;
//    fragNorm = objectNormalToWorld(model, normal);
    vec4 pos = mvp * newPos;
    gl_Position = pos;
}
