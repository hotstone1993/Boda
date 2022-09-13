#version 320 es

in vec4 vertexPosition;
in vec3 vertexNormal;
out vec3 fragColour;
uniform mat4 projection;
uniform mat4 modelView;
void main()
{
    fragColour = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    gl_Position = projection * modelView * vertexPosition;
}
