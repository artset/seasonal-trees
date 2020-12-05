#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

in vec3 position;
in vec3 normal;

out vec3 fragPos;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;

void main(void) {
    fragPos = (model * vec4(position, 1)).xyz;
    vec4 pos = mvp * vec4(position, 1);
    gl_Position = pos;


    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
    vec3 B = cross(N, T);
    mat3 TBN = mat3(T, B, N);
}
