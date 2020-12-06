#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;

out vec3 tangentFragPos;
out vec3 surfaceNormal;
out vec2 texCoords;
out vec3 tangentLightPos;
out vec3 tangentViewPos;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;

uniform mat4 view;
const vec3 lightPos = vec3(2, 2, 2);
//uniform vec3 lightPos;
//uniform vec3 viewPos;

void main(void) {
    vec4 pos = mvp * vec4(position, 1);
    gl_Position = pos; // wtf is this??

    vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    T = normalize(T - dot(T, N) * N); // Gram-Schmidt re-orthogonalization of T w.r.t. N (gives slightly nicer results)
    vec3 B = cross(N, T);
    mat3 TBN = mat3(T, B, N);
    // We can transpose here instead of inversing because TBN is orthogonal => TBN^T == TBN^(-1)
    mat3 TBN_inv = transpose(TBN);

    vec3 viewPos = (inverse(view) * -1.0 * view * model * vec4(position, 0.0)).xyz;

    tangentFragPos = (model * vec4(position, 1.0)).xyz;//TBN_inv * (model * vec4(position, 1.0)).xyz;
    surfaceNormal = N;
    texCoords = aTexCoords;
    tangentLightPos = lightPos;//TBN_inv * lightPos;
    tangentViewPos = viewPos;//TBN_inv * viewPos;
}
