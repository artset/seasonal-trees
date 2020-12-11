#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;

out vec3 fragPos;
out vec3 surfaceNormal;
out vec2 texCoords;
out vec3 lightPos;
out vec3 viewPos;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;

uniform mat4 view;
const vec3 testLightPos = vec3(0, 0, 3);
//uniform vec3 lightPos;

void main(void) {
    vec4 pos = mvp * vec4(position, 1);
    gl_Position = pos;

    fragPos = (model * vec4(position, 1.0)).xyz;
    surfaceNormal = normal;
    texCoords = aTexCoords;
    lightPos = testLightPos;
    viewPos = (inverse(view) * -1.0 * view * model * vec4(position, 0.0)).xyz;
}
