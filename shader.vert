#version 330 core

layout(location = 0) in vec3 ObjectSpace_position; // object-space vertex position
layout(location = 1) in vec3 ObjectSpace_normal;   // object-space vertex normal

uniform mat4 model, view, projection;

out vec3 normal;
out vec3 position;

void main() {

    gl_Position = projection * view * model * vec4(ObjectSpace_position, 1.0);
    normal = vec3(model * vec4(ObjectSpace_normal, 0.0));
    position = vec3(model * vec4(ObjectSpace_position, 1.0));
}
