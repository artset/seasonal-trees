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
    vec3 v = normalize(vertexToCamera);
    // TODO: fill the rest in

    //Sample the cube map to determine the reflection color.
    vec3 incident = reflect(cameraToVertex, n);
    vec4 worldIncident = inverse(view) * vec4(incident, 0.f);
    vec4 reflColor = texture(envMap, worldIncident.xyz);

    vec4 rDir = inverse(view) * vec4(refract(cameraToVertex, n, eta.r), 0.f);
    vec4 gDir = inverse(view) * vec4(refract(cameraToVertex, n, eta.g), 0.f);
    vec4 bDir = inverse(view) * vec4(refract(cameraToVertex, n, eta.b), 0.f);

    vec4 rSample = texture(envMap, rDir.xyz);
    vec4 gSample = texture(envMap, gDir.xyz);
    vec4 bSample = texture(envMap, bDir.xyz);
    vec4 refracColor = vec4(rSample.x ,gSample.y, bSample.z, 0.f);

//    // Compute F
    float thetaI = acos(dot(n, v)); // angle between surface normal and vector from camera to vertex
    float F = r0 + (1 - r0) * pow(1 - thetaI, 5);

    fragColor = mix(refracColor, reflColor, F);
}
