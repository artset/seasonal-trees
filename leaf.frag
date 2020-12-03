#version 400 core

in vec3 fragPos;
//in vec4 color;
out vec4 fragColor;

uniform float time;


vec4 getColor() {
    float r = (sin(time/1.5)+1)/2;
    float g = (sin(time/1.5*1.3)+1)/2;
    float b = (sin(time/1.5*1.6)+1)/2;
    return vec4(r,g,b,1);
}

void main() {
    fragColor = vec4(0.f, 168.f, 0.f, 1.f);
//    fragColor = color;
}
