#version 320 es

precision mediump float;
in vec3 fragPos;
in vec3 fragNormal;
out vec4 resultColor;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float alpha;
uniform float ks;

void main()
{
    vec3 d = normalize(vec3(0.0f ,0.0f, 0.0f) - fragPos);
    float diff = max(dot(fragNormal, d), 0.0f);
    vec3 reflectDir = (2.0f * dot(fragNormal, d) * fragNormal) - d;
    float spec = pow(max(dot(vec3(0, 0, -1), reflectDir), 0.0f), alpha);
    vec3 fragColour = ambient + diffuse * diff + specular * ks * spec;

    resultColor = vec4(fragColour, 1.0);
}