#version 400 core

in vec3 tangentFragPos;
in vec2 texCoords;
in vec3 tangentLightPos;
in vec3 tangentViewPos;

//uniform vec4 color;
const vec4 color = vec4(0, 1.0, 0, 1);
out vec4 fragColor;

uniform float time;
uniform sampler2D normalMap;

const float ambientIntensity = 0.2;
const float diffuseIntensity = 0.7;
const float specularIntensity = 0.7;
const float shininess = 40.0;

const float attConstant = 0.0;
const float attLinear = 0.0;
const float attQuadratic = 1.0;

const vec4 lightColor = vec4(1.0,1.0,1.0,1);
const float lightIntensity = 5.0;

void main() {
    fragColor = texture(normalMap, texCoords);
    fragColor = vec4(1,1,1,1);

//    vec3 tangentNormal = texture(normalMap, texCoords).rgb;
//    tangentNormal = normalize(tangentNormal * 2.0 - 1.0);

//    vec4 N = vec4(tangentNormal, 0);
//    vec4 L = vec4(normalize(tangentLightPos - tangentFragPos), 0);
//    vec4 V = vec4(normalize(tangentViewPos - tangentFragPos), 0);
//    vec4 R = normalize(reflect(L, N));

//    // compute lighting...
//    float d = sqrt(
//                pow(tangentLightPos.x - tangentFragPos.x, 2) +
//                pow(tangentLightPos.y - tangentFragPos.y, 2) +
//                pow(tangentLightPos.z - tangentFragPos.z, 2));

//    vec4 ambient = color * ambientIntensity;
//    vec4 diffuse = color * lightColor * diffuseIntensity * clamp(dot(N, L), 0.0, 1.0);
//    vec4 specular = color * lightColor * specularIntensity * pow(clamp(dot(V, R), 0.0, 1.0), shininess);
//    vec4 attenuation = color * lightIntensity * min(1.0, 1 / (attConstant + attLinear * d + attQuadratic * pow(d, 2)));

//    fragColor = ambient + attenuation * (diffuse + specular);
}
