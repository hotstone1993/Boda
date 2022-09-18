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

vec4 PointLight(vec3 vPosition, vec3 vNormal)
{
    vec3 toLight = lightPosition - vPosition;
    float fDistance = length(toLight);

    float fSpecularFactor = 0.0f;
    toLight /= fDistance;
    float fDiffuseFactor = dot(toLight, vNormal);
    if (fDiffuseFactor > 0.0f)
    {
        vec3 vReflect = reflect(-toLight, vNormal);
        fSpecularFactor = pow(max(dot(vReflect, cameraPosition), 0.0f), alpha);
        return vec4((ambient + (fDiffuseFactor * diffuse) + (fSpecularFactor * specular) * ks), 1.0f);
    }

    return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main()
{
    resultColor = PointLight(fragPos, fragNormal);
}