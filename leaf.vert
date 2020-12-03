#version 400 core

in vec3 position;
in vec3 normal;

out vec3 fragPos;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 trans;

//in vec4 color;
//out vec4 colorV;

void main(void) {
    fragPos = (model * vec4(position, 1)).xyz;
    vec4 pos = mvp * vec4(position, 1);
//    colorV = color;
    gl_Position = pos;
}
