#version 400 core

in vec3 fragPos;
in vec3 surfaceNormal;
in vec2 texCoords;
in vec3 lightPos;
in vec3 viewPos;

//uniform vec4 color;
const vec4 ambientColor = vec4(1, 1, 1, 1);
const vec4 diffuseColor = vec4(.32,.19,.09, 1);
const vec4 specularColor = vec4(1, 1, 1, 1);
out vec4 fragColor;

uniform float time;
uniform sampler2D sampler;

const float ambientIntensity = 0.2;
const float diffuseIntensity = 0.7;
const float specularIntensity = 0.7;
const float shininess = 40.0;

const float attConstant = 0.0;
const float attLinear = 0.0;
const float attQuadratic = 1.0;

const vec4 lightColor = vec4(1.0,1.0,1.0,1);
const float lightIntensity = 5.0;

const float blend = .2;

void main() {
    vec4 uvColor = texture(sampler, texCoords);
    vec4 N = vec4(normalize(surfaceNormal), 0);
    vec4 L = vec4(normalize(lightPos - fragPos), 0);
    vec4 V = vec4(normalize(viewPos - fragPos), 0);
    vec4 R = normalize(reflect(L, N));

    float d = sqrt(
                pow(lightPos.x - fragPos.x, 2) +
                pow(lightPos.y - fragPos.y, 2) +
                pow(lightPos.z - fragPos.z, 2));

    vec4 ambient = ambientColor * ambientIntensity;
    vec4 diffuse = diffuseColor * lightColor * diffuseIntensity * clamp(dot(N, L), 0.0, 1.0);
    diffuse = blend * uvColor + (1 - blend) * diffuse;
    vec4 specular = specularColor * lightColor * specularIntensity * pow(clamp(dot(V, R), 0.0, 1.0), shininess);
    float attenuation = lightIntensity * min(1.0, 1 / (attConstant + attLinear * d + attQuadratic * pow(d, 2)));

    fragColor = ambient + attenuation * (diffuse + specular);
//    fragColor = mix(uvColor, vec4(surfaceNormal, 1.0), 0.8);
}
