#version 330 core

in vec3 position;               // Position in object space
in vec3 normal;                 // Normal in object space

out vec3 vertex;                // Vertex position in camera space
out vec3 vertexToLight;         // Vector from the vertex to the light
out vec3 vertexToCamera;        // Vector from the vertex to the eye, which is the camera
out vec3 eyeNormal;             // Normal in eye space

//// Transformation matrices
uniform mat4 model;             // model matrix
uniform mat4 view;              // view matrix
uniform mat4 projection;        // projection matrix

uniform vec4 lightPosition;


vec4 scaleCylinder(vec4 pos) {
    vec4 newPos = pos;

    float yRange = newPos.y + .5f; // range from 0 to 1.
    float newScale = (1 - yRange);
    float b = 0;

    newPos.z = (newPos.z * newScale);
    newPos.z = (newPos.z * newScale);


    return newPos;
}


void main()
{
    vec4 newPos = vec4(position, 1.0);
    newPos = scaleCylinder(newPos);


    vertex = ((view*model)*newPos).xyz;
    vec4 camLightPosition = view*model*lightPosition;           // Light position in camera space
    vertexToLight = normalize(camLightPosition.xyz - vertex);
    vertexToCamera = -normalize(vertex);
    eyeNormal = normalize(mat3(transpose(inverse(view*model))) * normal);
    gl_Position = projection*view*model*newPos;

}
