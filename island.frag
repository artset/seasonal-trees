#version 400 core

in vec3 fragPos;
//in vec3 fragNorm;
//in vec4 color;
out vec4 fragColor;

uniform float time;


void main() {
    fragColor = vec4(146.f, 219.f, 110.f, 1.f);
//    fragColor = color;
}
