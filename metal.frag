#version 330 core

in vec3 vertex;                 // The position of the vertex, in camera space
in vec3 vertexToLight;          // Vector from the vertex to the light
in vec3 vertexToCamera;            // Vector from the vertex to the eye
in vec3 eyeNormal;		// Normal of the vertex, in camera space

uniform samplerCube envMap;	// The cube map containing the environment to reflect
uniform vec4 ambient;		// The ambient channel of the color to reflect
uniform vec4 diffuse;		// The diffuse channel of the color to reflect
uniform vec4 specular;		// The specular channel of the color to reflect

uniform mat4 model;             // model matrix
uniform mat4 view;              // view matrix
uniform mat4 mvp;               // model view projection matrix

uniform float r0;		// The Fresnel reflectivity when the incident angle is 0
uniform float m;		// The roughness of the material

out vec4 fragColor;

void main()
{
    vec3 n = normalize(eyeNormal);
    vec3 l = normalize(vertexToLight);
    vec3 cameraToVertex = normalize(vertex); //remember we are in camera space!

    //TODO: fill the rest in
    float termAmbient = 1.0;
    float termDiffuse = clamp(dot(n, l), 0.0, 1.0);

    vec3 v = normalize(vertexToCamera);
    vec3 u = l;
    vec3 h = normalize(u + v);

    float alpha = acos(dot(n, h));
    float D = exp(-pow(tan(alpha), 2) / pow(m, 2)) / (4.0 * pow(m, 2) * pow(cos(alpha), 4));

    float partialG = (2.0 * dot(h, n)) / dot(v, h);
    float G = min(1.0, min(partialG * dot(v, n), partialG * dot(u, n)));

    float cosTheta_i = dot(cameraToVertex, n);
    float F = r0 + (1.0 - r0) * pow(1 - cosTheta_i, 5);

    float termSpecular = clamp((D * G * F) / dot(v, n), 0.0, 1.0);

    vec4 objColor = termAmbient * ambient + termDiffuse * diffuse + termSpecular * specular;

    mat4 cameraToWorld = inverse(model * view);

    vec3 reflected = normalize(reflect(cameraToVertex, n));
    vec3 reflectedWsc = normalize((cameraToWorld * vec4(reflected, 0)).xyz);
    vec4 reflectedColor = texture(envMap, reflectedWsc);

    float cosTheta_i_reflect = dot(-cameraToVertex, n);
    float F_reflect = r0 + (1.0 - r0) * pow(1.0 - cosTheta_i_reflect, 5);

    vec4 finalColor = mix(objColor, reflectedColor, F_reflect);

    fragColor = finalColor;
}
