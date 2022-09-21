#version 320 es

in vec4 vertexPosition;
in vec3 vertexNormal;
out vec3 fragPos;
out vec3 fragNormal;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 world;

void main()
{
    fragPos = (world * vertexPosition).xyz;
    fragNormal = normalize((world * vec4(vertexNormal, 0.0)).xyz);
    gl_Position = projection * view * world * vertexPosition;
}