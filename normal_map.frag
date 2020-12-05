#version 400 core

//in vec3 tangentFragPos;
//in vec2 texCoords;
//in vec3 tangentLightDir;
//in vec3 tangentViewDir;

//uniform vec4 color;
//out vec4 fragColor;

//uniform float time;
//uniform sampler2D normalMap;

//void main() {
//    fragColor = vec4(0, 0, 255, 1);

//    vec3 n = texture(normalMap, texCoords).rgb;
//    n = normalize(n * 2.0 - 1.0);

//    // compute lighting...
//}

in vec3 fragPos;

uniform vec4 color;
out vec4 fragColor;

uniform float time;

vec4 getColor() {
    float r = (sin(time/1.5)+1)/2;
    float g = (sin(time/1.5*1.3)+1)/2;
    float b = (sin(time/1.5*1.6)+1)/2;
    return vec4(r,g,b,1);
}

void main() {
    fragColor = vec4(255, 255, 255, 1);
}
