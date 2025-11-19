#version 120

varying vec3 vNormal;
varying vec3 vPosition;
varying vec2 vTexCoord;
varying vec4 vColor;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vNormal = normalize(gl_NormalMatrix * gl_Normal);
    vPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    vTexCoord = vec2(gl_MultiTexCoord0);
    vColor = gl_Color;
}
