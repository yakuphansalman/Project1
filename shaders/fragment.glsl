#version 330 core

#define MAX_LIGHTS 100

out vec4 fragColor;

uniform vec4 uColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D ourTexture;
//Light uniforms
struct Light{
    vec3 position;
    int isActive;
    vec3 color;
    float intensity;
};
layout(std140) uniform LightBlock{
    Light lights[MAX_LIGHTS];
};
uniform int uLightCount;

uniform vec3 uEye;

void main()
{
    float ambientStrength = 0.2;
    float specularStrength = 0.5;

    vec3 norm = normalize(normal);

    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for (int i = 0; i < uLightCount; i++) {
        if(lights[i].isActive == 0) continue;

        vec3 lightColor = lights[i].color * lights[i].intensity;
        vec3 lightDir   = normalize(lights[i].position - fragPos);

        float distance    = length(lights[i].position - fragPos);
        float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
        // buradaki 0.09 ve 0.032 değerleri deneme amaçlıdır, istediğin etki için ayarlayabilirsin

        // Ambient
        ambient += ambientStrength * lightColor * attenuation;

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * lightColor * attenuation;

        // Specular
        vec3 viewDir = normalize(uEye - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        specular += specularStrength * spec * lightColor * attenuation;
    }
    vec3 result = (ambient + diffuse + specular); //* texture(ourTexture, texCoord).rgb;
    fragColor = vec4(result, 1.0)*uColor;
}