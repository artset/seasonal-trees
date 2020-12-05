#version 400 core

in vec3 tangentFragPos;
in vec2 texCoords;
in vec3 tangentLightPos;
in vec3 tangentViewPos;

uniform vec4 color;
out vec4 fragColor;

uniform float time;
uniform sampler2D normalMap;

void main() {
    fragColor = vec4(texCoords, 0, 1);

    vec3 n = texture(normalMap, texCoords).rgb;
    n = normalize(n * 2.0 - 1.0);
    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);

    // compute lighting...
}
