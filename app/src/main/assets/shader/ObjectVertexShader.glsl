#version 320 es

in vec4 vertexPosition;
in vec3 vertexNormal;
out vec3 fragPos;
out vec3 fragNormal;
uniform mat4 projection;
uniform mat4 modelView;

void main()
{
    fragPos = (modelView * vertexPosition).xyz;
    fragNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    gl_Position = projection * modelView * vertexPosition;
}