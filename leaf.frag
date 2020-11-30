#version 400 core

in vec3 fragPos;

out vec4 fragColor;

uniform float time;

void main() {
    fragColor = vec4(255.f, 0.f, 0.f, 0.f);
}
