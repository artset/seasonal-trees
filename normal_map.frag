#version 400 core

in vec3 tangentFragPos;
in vec3 surfaceNormal;
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
    vec4 n = normalize(surfaceNormal);
    vec4 L = normalize(vec4(tangentLightPos, 1.0) - tangentFragPos);
    vec4 E = normalize(Camera_position);
    vec4 R = normalize(reflect(L, n));
    float d = sqrt(
                pow(tangentLightPos.x - tangentFragPos.x, 2) +
                pow(tangentLightPos.y - tangentFragPos.y, 2) +
                pow(tangentLightPos.z - tangentFragPos.z, 2));

    float ambient = ambientIntensity;
    float diffuse = lightColor * diffuseIntensity * clamp(dot(n, L), 0, 1);
    float specular = lightColor * specularIntensity * pow(clamp(dot(E, R), 0, 1), shininess);
    float attenuation = lightIntensity * min(1, 1 / (attConstant + attLinear * d + attQuadratic * pow(d, 2)));

    fragColor = color * (ambient + attenuation * (diffuse + specular);
}
