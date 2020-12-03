#version 400 core

in vec3 fragPos;
uniform vec4 color;
uniform vec4 test;
out vec4 fragColor;

uniform float time;


void main() {
    fragColor = vec4(168.f, 168.f, 0.f, 0.f);
//    fragColor = color;

}
