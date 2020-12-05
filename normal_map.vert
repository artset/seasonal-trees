#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 aBitangent; // remove this

out vec3 tangentFragPos;
out vec2 texCoords;
out vec3 tangentLightDir;
out vec3 tangentViewDir;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main(void) {
    vec4 pos = mvp * vec4(position, 1);
    gl_Position = pos; // wtf is this??

    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    T = normalize(T - dot(T, N) * N); // Gram-Schmidt re-orthogonalization of T w.r.t. N (gives slightly nicer results)
    vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
    vec3 B = cross(N, T);
    mat3 TBN = mat3(T, B, N);
    // We can transpose here instead of inversing because TBN is orthogonal => TBN^T == TBN^(-1)
    mat3 TBN_inv = transpose(TBN);

    tangentFragPos = TBN_inv * (model * vec4(position, 1.0)).xyz;
    texCoords = aTexCoords;
    tangentLightDir = TBN_inv * normalize(lightPos - fragPos);
    tangentViewDir = TBN_inv * normalize(viewPos - fragPos);
}
