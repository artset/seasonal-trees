#version 400 core

in vec3 fragPos;
//in vec4 color;
out vec4 fragColor;

uniform float time;


void main() {
    fragColor = vec4(0.f, 168.f, 0.f, 0.f);
//    fragColor = color;
}
