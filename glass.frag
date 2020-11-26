#version 330 core

in vec3 vertex;                 // The position of the vertex, in camera space!
in vec3 vertexToCamera;         // Vector from the vertex to the eye, which is the camera
in vec3 eyeNormal;	        // Normal of the vertex, in camera space!

uniform float r0;		// The R0 value to use in Schlick's approximation
uniform float eta1D;		// The eta value to use initially
uniform vec3  eta;              // Contains one eta for each channel (use eta.r, eta.g, eta.b in your code)

uniform mat4 view;
uniform mat4 model;

uniform samplerCube envMap;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(eyeNormal);
    vec3 cameraToVertex = normalize(vertex); //remember we are in camera space!
    vec3 vertexToCamera = normalize(vertexToCamera);
    // TODO: fill the rest in

    mat4 cameraToWorld = inverse(model * view);

    vec3 reflected = normalize(reflect(cameraToVertex, n));
    vec3 reflectedWsc = normalize((cameraToWorld * vec4(reflected, 0)).xyz);
    vec4 reflectedColor = texture(envMap, reflectedWsc);

    vec3 R = normalize((cameraToWorld * vec4(refract(cameraToVertex, n, eta.r), 0)).xyz);
    vec3 G = normalize((cameraToWorld * vec4(refract(cameraToVertex, n, eta.g), 0)).xyz);
    vec3 B = normalize((cameraToWorld * vec4(refract(cameraToVertex, n, eta.b), 0)).xyz);

    float red = texture(envMap, R).r;
    float green = texture(envMap, G).g;
    float blue = texture(envMap, B).b;
    vec4 refractedColor = vec4(red, green, blue, 1);

    float cosTheta_i = dot(cameraToVertex, n);
    float F = r0 + (1.0 - r0) * pow(1.0 - cosTheta_i, 5);

    vec4 finalColor = mix(reflectedColor, refractedColor, F);

    fragColor = finalColor;
}
