#version 320 es

precision mediump float;
in vec3 fragColour;
out vec4 resultColor;
void main()
{
    resultColor = vec4(fragColour, 1.0);
}