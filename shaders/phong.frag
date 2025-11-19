#version 120

varying vec3 vNormal;
varying vec3 vPosition;
varying vec2 vTexCoord;
varying vec4 vColor;

uniform vec3 uLightDir;
uniform vec3 uLightColor;
uniform vec3 uAmbientColor;
uniform vec3 uSpecularColor;
uniform sampler2D uTexture;
uniform int uUseTexture;
uniform float uShininess;

void main()
{
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(-uLightDir);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 baseColor = vColor.rgb;
    if (uUseTexture == 1)
    {
        baseColor *= texture2D(uTexture, vTexCoord).rgb;
    }

    vec3 color = uAmbientColor * baseColor + diff * baseColor * uLightColor;

    vec3 viewDir = normalize(-vPosition);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), uShininess);
    color += uSpecularColor * spec;

    gl_FragColor = vec4(color, vColor.a);
}
