#version 400 core

in vec3 fragPos;

uniform vec4 color;
out vec4 fragColor;

uniform float time;
uniform sampler2D normalMap;



void main() {
    fragColor = vec4(0, 0, 255, 1);

    vec3 n = texture(normalMap, fragPos.TexCoords);
    n = normalize(n * 2.0 - 1.0);
}
