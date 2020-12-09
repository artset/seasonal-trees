#version 400 core

uniform vec4 color;
out vec4 fragColor;
uniform float time;

void main() {
    fragColor = color;
}
