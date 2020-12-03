#version 330 core

uniform mat4 model, view, projection;

// Light properties
const vec3 WorldSpace_lightPos = vec3(2, 2, 2); // world-space light position
uniform vec3 lightColor;
uniform float lightIntensity;

// Attenuation Properties
uniform float attQuadratic;
uniform float attLinear;
uniform float attConstant;

// Material properties
uniform vec3 color;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform float shininess;

in vec3 normal;
in vec3 position;

out vec3 fragColor;

void main(){

    fragColor = color*ambientIntensity;
//    vec3 L = (view*vec4(WorldSpace_lightPos-position, 1)).xyz;
    vec3 L  = vec3(WorldSpace_lightPos - position);
    float d = sqrt(pow(L[0], 2) + pow(L[1],2) + pow(L[2], 2));
    float attenuation = lightIntensity * min(1/(attConstant + attLinear*d + attQuadratic*pow(d,2)), 1);
    fragColor += color * lightColor * diffuseIntensity * (dot(normalize(normal), normalize(L))) * attenuation;

    vec3 newL = vec3(position - WorldSpace_lightPos);
    vec4 eyeVector = vec4(inverse(view)*vec4(0.0, 0.0, 0.0, 1.0) - vec4(position,1));
    vec4 reflectionVector = vec4(reflect(normalize(newL), normalize(normal)), 1);
    float dotProduct = dot(normalize(eyeVector), reflectionVector);
    fragColor += color * lightColor * specularIntensity * pow(max(0, dotProduct), shininess) * attenuation;

//    fragColor += color * lightColor * specularIntensity * pow(max(0, dot(normalize(-position), reflect(-L, normalize(normal)))), shininess) * attenuation;

}
